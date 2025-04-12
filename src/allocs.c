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
    unsigned long size = 640 * 480;
    t_rgb *buffer = (t_rgb *)malloc(sizeof(t_rgb) * size); // Allocate memory for RGB buffer

    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Can't allocate memory.\n");
        return 1;
    }

    // Set a pixel's color as a test
    buffer[42] = (t_rgb){64, 64, 64};

    FILE *file = fopen("RAMDUMP.ppm", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file.\n");
        free(buffer);
        return 1;
    }

    // Write PPM header and pixel data
    fprintf(file, "P6\n# RAMDUMP.ppm\n%d %d\n255\n", 640, 480);
    fwrite(buffer, sizeof(t_rgb), size, file);

    fclose(file);
    free(buffer);

    printf("Done.\n");
    return 0;
}

int allocget(void)
{
    int buf_size = 4;
    while (1)
    {
        char *user_input = (char *)calloc(buf_size + 1, sizeof(char)); // Allocate memory for user input
        if (!user_input)
        {
            fprintf(stderr, "Error: Can't allocate memory.\n");
            return 1;
        }

        printf("Input a string: ");
        if (fgets(user_input, buf_size + 1, stdin) != NULL)
        {
            // Check for end of line; flush input buffer if needed
            size_t len = strlen(user_input);
            if (len > 0 && user_input[len - 1] != '\n')
            {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }

            char formatted_input[3] = ""; // Only store first 2 characters
            sscanf(user_input, " %2c", formatted_input);
            printf("First two characters: %s\n", formatted_input);
        }
        else
        {
            if (feof(stdin))
                break; // End of input
            perror("Error reading input");
            free(user_input);
            return 1;
        }

        free(user_input);
    }
    return 0;
}

int allocs(void)
{
    char a[] = "Hello,";
    char b[] = " world!";
    char s[10];

    size_t a_len = strlen(a);
    size_t b_len = strlen(b);
    size_t cat_len = a_len + b_len;
    char *cat = (char *)calloc(cat_len + 1, sizeof(char)); // Allocate memory for concatenated string

    if (!cat)
    {
        fprintf(stderr, "Error: Can't allocate memory.\n");
        return 1;
    }

    strncpy(cat, a, a_len);
    strncat(cat, b, b_len);

    strncpy(s, a + 3, 5);
    s[5] = '\0'; // Ensure null termination

    printf("a: %s\nb: %s\ns: %s\nr: %s\n", a, b, s, cat);
    free(cat);

    return 0;
}

int strallo(void)
{
    char buf[1024], *p_buf;
    char **strings = malloc(sizeof(char *));
    int c;
    size_t numStrings = 0;

    if (strings == NULL)
    {
        fprintf(stderr, "Error: Can't allocate memory.\n");
        return 1;
    }

    p_buf = buf;

    while ((c = fgetc(stdin)) != EOF)
    {
        if (c == '\n')
        {
            *p_buf = '\0';
            strings[numStrings] = malloc(strlen(buf) + 1);
            if (strings[numStrings] == NULL)
            {
                fprintf(stderr, "Error: Can't allocate memory.\n");
                return 1;
            }
            strcpy(strings[numStrings], buf);
            numStrings++;
            strings = realloc(strings, (numStrings + 1) * sizeof(char *));
            if (strings == NULL)
            {
                fprintf(stderr, "Error: Can't reallocate memory.\n");
                return 1;
            }
            p_buf = buf; // Reset buffer pointer
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
