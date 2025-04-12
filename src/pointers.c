#include <stdio.h>
#include <stdlib.h>

void matrix(){
    
    int *p = (int *)0x3F8;
    int *p1 = (int *) 1500;
    printf("Pointers:\n%p, %p\n%d, %d\n%p %p", p,p1,p,p1,&p,&p1);

    int i = 5;
    int j = 6;
    int k = 7;

    // Dynamically allocate memory for the matrix
    int*** matrix = (int***)malloc(i * sizeof(int**));
    for (int x = 0; x < i; x++) {
        matrix[x] = (int**)malloc(j * sizeof(int*));
        for (int y = 0; y < j; y++) {
            matrix[x][y] = (int*)malloc(k * sizeof(int));
        }
    }

    // Assign values to the matrix
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            for (int z = 0; z < k; z++) {
                matrix[x][y][z] = x * j * k + y * k + z;
            }
        }
    }

    // Print the matrix visualization
    for (int x = 0; x < i; x++) {
        printf("Layer %d:\n", x);
        for (int y = 0; y < j; y++) {
            for (int z = 0; z < k; z++) {
        printf("\n%p %p %p\n%d %d %d", *(*(matrix + x)+y), *(matrix + x), (matrix + x), x, i, z);
printf("%3d ", *(*(*(matrix + x) + y) + z));
            }
            printf("\n");
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    for (int x = 0; x < i; x++) {
        for (int y = 0; y < j; y++) {
            free(matrix[x][y]);
        }
        free(matrix[x]);
    }
    free(matrix);
}
int ptrs() {
    int a, *b, **c, ***d;

    printf("Enter a value for a: ");
    if (scanf("%d", &a) != 1) {
        printf("Invalid input. Exiting...\n");
        return 1;
    }

    b = &a;
    c = &b;
    d = &c;

    if (b == NULL || c == NULL || d == NULL) {
        printf("Error assigning pointers. Exiting...\n");
        return 1;
    }

    *b = 2 * a;
    printf("b: %d\n", *b);
    **c = 3 * a;
    printf("c: %d\n", **c);
    ***d = 4 * a;

    printf("d: %d\n", ***d);

    return 0;
}
#include <stdio.h>

#define ROWS 5
#define COLS 8

void printVector(int *vec, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", *(vec + i * cols + j));
        }
        printf("\n");
    }
}

int vec() {
    int vector[ROWS][COLS];

    printf("Enter the elements of the vector (5x8):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            scanf("%d", &vector[i][j]);
        }
    }

    printf("\nVector:\n");
    printVector(&vector[0][0], ROWS, COLS);

    return 0;
}