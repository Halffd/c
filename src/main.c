#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lib.h"


int ac;
char** av;
FILE* f;

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
    f = nfile("file");
   
    //c99();
    //defn();
    adv();
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
