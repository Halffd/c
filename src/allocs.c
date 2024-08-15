#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} t_rgb;

int imgs(void)
{
    t_rgb *buffer = NULL;
    unsigned long size = 640 * 480;

    // buffer = (t_rgb *) malloc( sizeof(t_rgb) * size );
    buffer = (t_rgb *)malloc(3 * sizeof(unsigned char) * size);

    buffer[42] = (t_rgb){64, 64, 64};

    if (buffer == NULL)
    {
        printf("Can't allocate memory.\n");
    }
    else
    {
        FILE *file;
        file = fopen("RAMDUMP.ppm", "wb");

        if (file == NULL)
        {
            printf("Can't open file.\n");
        }
        else
        {
            // Basic PPM image file
            fprintf(file, "P6\n# RAMDUMP.ppm\n%d %d\n255\n", 640, 480);
            fwrite(buffer, sizeof(t_rgb), size, file);
        }

        fclose(file);

        free(buffer);

        printf("Done.\n");
    }

    return 0;
}
int allocget()
{

 // Will loop until EOF or error.
 int buf_size = 4;
 while (1)
 {
 char *user_input = calloc(1, buf_size*sizeof(char));
 printf("Input a string: ");
 // Handle user input.
 if (fgets(user_input, buf_size+1, stdin) != NULL)
 {
 // "Flush" stdin if string doesn't end with \n\0.
 size_t len = strlen(user_input);
 if (len > 0 && user_input[len-1] != '\n')
 {
 int c;
 while ((c = getchar()) != '\n' && c != EOF);
 }
 char *formatted_input = malloc(2*sizeof(char));
 // Strip whitespaces, take first 2 chars, and print.
 sscanf(user_input, " %2c", formatted_input);
 printf("First two characters: %s\n", formatted_input);
 // Free memory we aren't using anymore.
 free(formatted_input);
 formatted_input = NULL;
 }
 else
 {
 // Handle EOF and errors.
 if (errno != 0)
 {
 perror("fgets");
 exit(EXIT_FAILURE);
 }
 exit(EXIT_SUCCESS);
 }
 // Free memory we aren't using anymore.
 free(user_input);
 user_input = NULL;
 }
}
int allocs()
{
    char a[]= "Hello,";
    char b[] = " world!";
    char s[10];
size_t a_len = strlen(a);
size_t b_len = strlen(b);
size_t cat_len = a_len + b_len;
char *cat = calloc(cat_len + 1, sizeof(char));
strncpy(cat, a, a_len);
strncat(cat, b, b_len);
    strncpy(s, a + 3, 5);
    printf("a:%s\nb:%s\ns:%s\nr:%s / %p",a,b,s,cat);
}
int strallo(){
    char buf[1024], *p_buf;
    char **strings = malloc(sizeof(char *));
    int c;
    size_t numStrings = 0;

    p_buf = buf;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (c == '\n')
        {
            *p_buf = '\0';

            strings[numStrings] = malloc(strlen(buf) + 1);
            strcpy(strings[numStrings], buf);

            numStrings++;
            strings = realloc(strings, (numStrings + 1) * sizeof(char *));

            p_buf = buf; // Reset p_buf to the beginning of buf
        }
        else
        {
            *p_buf++ = c;
        }
    }

    printf("Strings:\n");
    for (size_t i = 0; i < numStrings; i++)
    {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    free(strings);

    return 0;
}