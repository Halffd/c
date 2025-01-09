#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lib.h"
#include "print.h"
#include "util.h"

int ac;
char** av;
FILE* f;

#ifdef _WIN32
#define DELIM "\\"
#else
#define DELIM "/"
#endif


typedef struct {
    char *base_path;
    char *full_path;
    StrArray *dirs;
    int dirCount;
    //char *(*file)(struct FileSystem *, const char *);
} FileSystem;


char* strdups(const char *s) {
    if (!s) return NULL; // Handle NULL input
    size_t len = strlen(s); // Get the length of the string
    char *copy = (char *)malloc(len + 1); // Allocate memory for the new string (+1 for null terminator)
    if (!copy) return NULL; // Check for allocation failure
    strcpy(copy, s); // Copy the string into the new memory
    return copy; // Return the duplicated string
}

// Function to construct a full file path
char *append_filename(FileSystem *fs, const char *filename) {
    size_t base_path_len = strlen(fs->base_path);
    size_t filename_len = strlen(filename);
    size_t full_path_len = base_path_len + filename_len + 2; // +2 for delim and '\0'

    char *full_path = malloc(full_path_len);
    if (!full_path) {
        perror("malloc");
        return NULL;
    }
    
    snprintf(full_path, full_path_len, "%s%s%s", fs->base_path, DELIM, filename);
    return full_path;
}

// Function to create a new file and write the current date and time
FILE *create_file(FileSystem *fs, const char *filename) {
    char *file_path = append_filename(fs, filename);
    if (!file_path) return NULL;

    FILE *file = fopen(file_path, "a");
    if (!file) {
        printf("Error creating file: %s\n", file_path);
        free(file_path);
        return NULL;
    }

    time_t current_time = time(NULL);
    struct tm *timeinfo = localtime(&current_time);
    char date_string[20];
    char time_string[80];

    strftime(date_string, sizeof(date_string), "%Y-%m-%d", timeinfo);
    strftime(time_string, sizeof(time_string), "%c", timeinfo);

    fprintf(file, "File created on: %s\n", date_string);
    fprintf(file, "Time: %s\n", time_string);

    fflush(file);
    free(file_path);
    return file;
}

// Function to initialize a FileSystem structure
FileSystem* create_filesystem(const char *base_path) {
    FileSystem *fs = (FileSystem *)malloc(sizeof(FileSystem));
    if (!fs) {
        perror("malloc");
        return NULL;
    }
    fs->full_path = strdups(base_path); // Duplicate the base path
    fs->dirs = split(fs->full_path, DELIM);
    del(fs->dirs, -1);
    #ifndef WINDOWS
    prepend(fs->dirs, "");
    #endif
    fs->dirCount = fs->dirs->size;
    fs->base_path = join(fs->dirs, DELIM);
    //fs->file = append_filename; // Set the file function pointer
    return fs;
}
// Function to free the FileSystem structure
void free_filesystem(FileSystem *fs) {
    free(fs->base_path);
    free(fs);
}

long srcSize(){
    FILE *file = fopen(__FILE__, "rb");  // Open the current source file

    if (file) {
        fseek(file, 0, SEEK_END);        // Move the file pointer to the end of the file
        long size = ftell(file);         // Get the current position, which represents the file size in bytes

        // printf("Size of current file: %ld bytes\n", size);

        fclose(file);                    // Close the file
        
        return size;
    } else {
        printf("Unable to open the file.\n");
    }
    return -1;
}
FILE* nfile(const char *file_path)
{
    // ...

    // Create a new file for writing the cleaned subtitles
    FILE *new_file = fopen(file_path, "a");
    if (new_file == NULL)
    {
        printf("Error creating file: %s\n", file_path);
        return NULL;
    }
    long size = srcSize();
    // Get the current date and time
    time_t current_time = time(NULL);
    struct tm *timeinfo = localtime(&current_time);
    char date_string[20];
    char txt[80];
    char hh[40];
    strftime(date_string, sizeof(date_string), "%Y-%m-%d", timeinfo);
    strftime(txt, 80, "%c", timeinfo);
    sprintf(hh, "%d", current_time);
     //strftime(hh, 20, "%H-%M-%S", timeinfo);
    time_t t = time(NULL);
    // replace localtime with gmtime if you want UTC time
    struct tm *buf = localtime(&t);
    // Write the date to the file
    fprintf(new_file, "%s ", date_string);
    fprintf(new_file, "%d %d\n%s (%s)\n\n", buf->tm_sec, size, txt, hh);

    fflush(new_file);
    // Close the file
    return new_file;

    // ...
}

int main(int argc, char *argv[]) 
{
    // Create the FileSystem with a base path
    FileSystem *fs = create_filesystem(argv[0]);
    if (!fs) {
        return EXIT_FAILURE;
    }

    // Create a file using the FileSystem
    f = create_file(fs, "output.txt");

    // Print filesystem information
    printf("Base path: %s\n", fs->base_path);
    char *path = append_filename(fs, "cfile.txt");
    nfile(path);
    // Clean up
    //prov(argc, argv);
    //c11();
    //pthr();
    //c99();
    c99_2();
    //defn();
    //adv();
    //lua(argc, argv);
    
    //est(argc, argv);
    //serial(argc, argv);
    //return server(argc, argv);
    //return chat(argc, argv);
    //FILE* read = fopen("file", "r");
    //int c = 
    
    //filesf(file, read);

    //subs();
    //pipes();
    //rev();
    //cmpss()
    //studs();
    //fclose(file);
    free_filesystem(fs);
    return 0;
}
