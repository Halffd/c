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

typedef struct {
    char *base_path;
    char *(*file)(const char *filename);
} file_system;
file_system fs;

// Function to append a filename to the base path
char *append_filename(const char *filename) {
    // Find the last backslash in the base path
    char *last_slash = strrchr(fs.base_path, '\\');

    // Calculate the required length for the full path string
    size_t base_path_len = last_slash ? (last_slash - fs.base_path + 1) : strlen(fs.base_path);
    size_t filename_len = strlen(filename);
    size_t full_path_len = base_path_len + filename_len + 1; // +1 for '\0'

    // Allocate memory for the full path string
    char *full_path = malloc(full_path_len);
    if (full_path == NULL) {
        perror("malloc");
        return NULL;
    }

    // Concatenate the base path and filename
    if (last_slash) {
        snprintf(full_path, full_path_len, "%s%s", fs.base_path, filename);
    } else {
        snprintf(full_path, full_path_len, "%s\\%s", fs.base_path, filename);
    }

    return full_path;
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
    ac = argc;
    av = argv;
    StrArray *dirs = split(argv[0], "\\");
    del(dirs, -1);
    set(dirs, -1, "log\\");
    fs.base_path = join(dirs, "\\");
    fs.file = append_filename;
    char *d = replace(argv[0], "build\\c.exe", "");
    char *dd = replace(d, "\\", "/");
    printw("Args: %s\nDir: %s\n---------------\n", argv[0], fs.base_path);
    f = nfile(fs.file("cfile.txt"));
    FILE *new_file = fopen(fs.file("testc"), "w");
    fprintf(new_file, "...");
    fclose(new_file);

    //prov(argc, argv);
    //c11();
    pthr();
    //c99();
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
    return 0;
}
