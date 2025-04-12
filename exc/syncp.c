#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pcre.h>

#define MAX_PATH 260
#define BUFFER_SIZE 1024

void prints(const char *format, const char *end, const char *delim, ...) {
    va_list args;
    va_start(args, delim);
    
    int first = 1; // To manage delimiters

    while (*format) {
        if (!first) {
            printf("%s", delim); // Print delimiter before subsequent arguments
        }

        switch (*format) {
            case 's': { // String
                const char *str = va_arg(args, const char *);
                printf("%s", str);
                break;
            }
            case 'd': { // Integer
                int i = va_arg(args, int);
                printf("%d", i);
                break;
            }
            case 'f': { // Float
                double f = va_arg(args, double);
                printf("%f", f);
                break;
            }
            case 'c': { // Character
                int c = va_arg(args, int); // char is promoted to int
                printf("%c", c);
                break;
            }
            default:
                printf("Unknown format specifier: %c", *format);
                break;
        }
        
        first = 0; // After the first argument
        format++; // Move to the next format specifier
    }

    printf("%s", end); // Print end string
    va_end(args);
}
// Simple printing without delimiters
void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    prints(format, "\n", "", args); // Call prints with newline as end
    va_end(args);
}
// Shortcut functions for printing single arguments of various types
void print1s(const char *str) {
    prints("s", "\n", "", str);
}
void print1d(int i) {
    prints("d", "\n", "", i);
}
void print1f(double f) {
    prints("f", "\n", "", f);
}
void print1c(char c) {
    prints("c", "\n", "", c);
}
// Function to extract the episode number from a filename using PCRE
char* extract_episode_number(const char* filename) {
    static char episode_number[10];
    pcre *re;
    const char *error;
    int erroffset;
    int ovector[30];
    int rc;

    // Compile regex for matching episode numbers
    const char *pattern = "(_\\d+)";
    re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return NULL;
    }

    // Execute the regex
    rc = pcre_exec(re, NULL, filename, strlen(filename), 0, 0, ovector, 30);
    if (rc >= 0) {
        // Extract the episode number
        int s = 2;
        int start = ovector[s]; // The end of the first capturing group
        int length = ovector[s+1] - ovector[s];
        strncpy(episode_number, filename + start, length);
        episode_number[length] = '\0'; // Null-terminate
        pcre_free(re);
        return episode_number;
    }

    pcre_free(re);
    return NULL;
}

// Function to check if a string matches a pattern using PCRE
int matches_pattern(const char* filename, const char* pattern) {
    pcre *re;
    const char *error;
    int erroffset;
    int ovector[30];
    int rc;

    // Compile the regex
    re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed at offset %d: %s\n", erroffset, error);
        return 0;
    }

    // Execute the regex
    rc = pcre_exec(re, NULL, filename, strlen(filename), 0, 0, ovector, 30);
    pcre_free(re);
    return rc >= 0; // Return true if there's a match
}

// Function to sync subtitles
void sync_subtitles(const char* video_dir, const char* srt_dir) {
    DIR* video_folder = opendir(video_dir);
    struct dirent* entry;

    if (!video_folder) {
        perror("Failed to open video directory");
        return;
    }

    while ((entry = readdir(video_folder)) != NULL) {
        if (strstr(entry->d_name, ".mkv")) {
            char video_path[MAX_PATH];
            snprintf(video_path, sizeof(video_path), "%s/%s", video_dir, entry->d_name);
            print("sss",video_path,video_dir, entry->d_name);
            char* episode_number = extract_episode_number(entry->d_name);
            print1s(episode_number);
            if (episode_number) {
                // Build the SRT pattern
                char srt_pattern[BUFFER_SIZE];
                snprintf(srt_pattern, sizeof(srt_pattern), "Pocket_Monsters_2019.*%s.*\\.srt", episode_number);
                print1s(srt_pattern);
                DIR* srt_folder = opendir(srt_dir);
                struct dirent* srt_entry;

                if (!srt_folder) {
                    perror("Failed to open subtitle directory");
                    continue;
                }

                while ((srt_entry = readdir(srt_folder)) != NULL) {
                    if (matches_pattern(srt_entry->d_name, srt_pattern)) {
                        char srt_path[MAX_PATH];
                        snprintf(srt_path, sizeof(srt_path), "%s/%s", srt_dir, srt_entry->d_name);
                        char output_srt_path[MAX_PATH];
                        snprintf(output_srt_path, sizeof(output_srt_path), "%s/corrected_%s", srt_dir, srt_entry->d_name);

                        // Construct the alass command
                        char command[BUFFER_SIZE];
                        snprintf(command, sizeof(command), "S:/Code/.mkv-subs/alass \"%s\" \"%s\" \"%s\" --disable-fps-guessing --split-penalty 10", 
                                 video_path, srt_path, output_srt_path);
                        
                        // Execute the command
                        printf("Running command: %s\n", command);
                        system(command);
                    }
                }
                closedir(srt_folder);
            }
        }
    }
    closedir(video_folder);
}

int main() {
    const char* video_dir = "E:/pokemon 2019"; // Adjust path as needed
    const char* srt_dir = "C:/Users/halff/Documents/Subs/pokemon 2019"; // Adjust path as needed

    sync_subtitles(video_dir, srt_dir);
    printf("Subtitle syncing completed.\n");
    return 0;
}