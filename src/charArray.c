#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lib.h"

#define ARRAY_X 50
#define ARRAY_Y 50
#define ARRAY_Z 10
char*** makeArray(int array_x, int array_y, int array_z) {
    char*** a3d = (char***)malloc(array_x * sizeof(char**));
    for (int i = 0; i < array_x; i++) {
        a3d[i] = (char**)malloc(array_y * sizeof(char*));
        for (int j = 0; j < array_y; j++) {
            a3d[i][j] = (char*)malloc(array_z * sizeof(char));
            // Initialize the memory block to null characters
            memset(a3d[i][j], '\0', array_z * sizeof(char));
        }
    }
    return a3d;
}

void charArray(){
    char*** a3d = makeArray(3,255,512);

    // Now you can access the 3D array as a3d[x][y][z]
    // For example, to set a value:
    a3d[0][20][0] = '-';
    a3d[0][20][1] = '-';
    a3d[0][20][2] = '-';
    a3d[0][20][3] = '-';
    a3d[0][20][4] = '-';
    a3d[0][20][5] = 'H';
    a3d[0][20][6] = 'e';
    a3d[0][20][7] = 'l';
    a3d[0][20][8] = 'l';
    a3d[0][20][9] = 'o';
    a3d[0][20][10] = ',';
    a3d[0][20][11] = ' ';
    a3d[0][20][12] = 'w';
    a3d[0][20][13] = 'o';
    a3d[0][20][14] = 'r';
    a3d[0][20][15] = 'l';
    a3d[0][20][16] = 'd';
    a3d[0][20][17] = '!';
    a3d[0][20][18] = '\0';

    // Reallocate the memory for a3d[0][25]
    a3d[0] = (char**)realloc(a3d[0], 25 * sizeof(char*));
    for (int i = 20; i < 25; i++) {
        a3d[0][i] = (char*)malloc(512 * sizeof(char));
        memset(a3d[0][i], '\0', 512 * sizeof(char));
    }

    // Set some other values
    strcpy(a3d[0][21], "other line!");
    strcpy(a3d[0][22], "another line!");
    strcpy(a3d[0][23], "and another!");
    strcpy(a3d[0][24], "the last one!");

    // Print the new lines
    for (int i = 20; i < 25; i++) {
        printf("%s\n", a3d[0][i]);
    }
    strcpy(a3d[1][0], "oth-er l-ine!");
    strcpy(a3d[1][1], "-ano-ther -line!");
    strcpy(a3d[2][254], "-last line!");

    // And to print a value:
    printf("%s\n", a3d[0][20]);
    printf("%s\n", a3d[1][0]);
    printf("%s\n", a3d[1][1]);
    printf("%s\n", a3d[2][254]);

    free(a3d);
}