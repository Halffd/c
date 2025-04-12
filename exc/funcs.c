#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM (sizeof(wlist) / sizeof(char *))

int main(void) {
    printf("Hello world!\n");

    // Removed unused code for clarity
    int x = 5;
    int y = 10;
    int z = 2;
    int pp = 3;
    int *p = &pp;

    struct {
        int x;
        int a;
    } s = {7, 4};

    union uis {
        char a;
        unsigned char b;
        long int c;
        double d;
        short e;
        float f;
        char g;
        short h;
    } ui;

    char input[32];

    printf("Enter a value for 'a': ");
    fgets(input, sizeof(input), stdin);
    ui.a = input[0];  // Assign the first character

    printf("Enter a value for 'b': ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%hhu", &ui.b);

    printf("Enter a value for 'g': ");
    fgets(input, sizeof(input), stdin);
    ui.g = input[0];

    // Print the values
    printf("Value of 'a': %c\n", ui.a);
    printf("Value of 'b': %u\n", ui.b);
    printf("Value of 'c': %ld\n", ui.c);
    printf("Value of 'd': %lf\n", ui.d);
    printf("Value of 'e': %hd\n", ui.e);
    printf("Value of 'g': %c\n", ui.g);

    // Treat the union as a block of memory
    unsigned char *mem = (unsigned char*)&ui;
    size_t size = sizeof(ui);

    // Print the values byte by byte
    for (size_t i = 0; i < size; i++) {
        printf("mem[%zu]: %u\n", i, mem[i]);
    }

    // Printing struct values as integers
    printf("Value of s.x: %d\n", s.x);
    printf("Value of s.a: %d\n", s.a);

    // Continue with calculations
    int temp = (int)((float)sizeof(*p) - (intptr_t)(&pp) * (++y) - (--(s.x))) << s.a;
    x += (x != 0) ? temp : z;
    printf("x = %d\n", x);

    return 0;
}

int dumbcmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int compare(const void *arg1, const void *arg2) {
    const int *a = arg1, *b = arg2;

    if (*a == *b)
        return 0;
    else if (*a < *b)
        return -1;
    else
        return 1;
}

#define NWIN 10
#define NNUM 25

void tmp() {
    for (int i = 1; i <= 100; i++) {
        char fb[32] = ""; // Initialize with an empty string

        // Check if i is divisible by 3 and append
        if (i % 3 == 0)
            strcat(fb, "Fizz");

        // Check if i is divisible by 5 and append
        if (i % 5 == 0)
            strcat(fb, "Buzz");

        // If fb is still empty, convert i to a string
        if (!fb[0])
            sprintf(fb, "%d", i);

        // Print the FizzBuzz result
        puts(fb);
    }

    const char *s = "2147483647";
    int n = atoi(s);
    if (n + 1 < n) {
        puts("Overflow!");
    } else {
        puts("No overflow");
    }
    printf("%d\n", n + 1);

    for (int i = -1; i >= -260; i--) {
        printf("Character code for %d: %c\n", i, (char)i);
    }

    int array[6] = {7, 2, 6, 1, 2, 5};
    qsort(array, 6, sizeof(array[0]), compare);

    for (int i = 0; i < 6; ++i) {
        printf("%d\n", array[i]);
    }

    char *wlist[] = {
        "aids", "crud", "evil", "gall", "idiot", "kick",
        "moon", "oval", "quod", "sulk", "under", "west",
        "year"};

    char *word = "evil";
    int found = (bsearch(&word, wlist, NUM, sizeof(char *), dumbcmp) != NULL);
    printf("%d\n", found);

    // Handle space counting
    int spaces_count = 0;
    int current_character;
    while ((current_character = getchar()) != EOF) {
        if (isspace(current_character))
            spaces_count++;
        else
            spaces_count = 0;

        if (spaces_count > 0)
            putchar(spaces_count);
    }

    // ... (rest of the code remains unchanged)
}