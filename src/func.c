#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void file(FILE* f){
    // Write the cleaned subtitles to the new file
    for (int i = 0; i < 11; i++)
    {
        char buffer[20];
        sprintf(buffer, "%d", i);
        if (fprintf(f, "%s\n", buffer) < 0)
        {
            perror("Error writing to file");
            return;
        }
    }
}
float factorial(float n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}
int dumbcmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}
int compare(const void *arg1, const void *arg2)
{
    const int *a = arg1, *b = arg2;

    if (*a == *b)
        return 0;
    else if (*a < *b)
        return -1;
    else
        return 1;
}