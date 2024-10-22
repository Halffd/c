#include <stdio.h>
#include <stdlib.h>

typedef struct VecInt {
    size_t size;
    size_t capacity;
    int* data;
} vec_int;

vec_int* vec_int_new(void) {
    vec_int* ret = malloc(sizeof(vec_int));
    ret->size = 0;
    ret->capacity = 4;  // Initial capacity of 4
    ret->data = malloc(ret->capacity * sizeof(int));
    return ret;
}

void vec_int_push(vec_int* vec, int new) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;  // Double the capacity
        vec->data = realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size] = new;
    vec->size++;
}

int vec_int_pop(vec_int* vec) {
    if (vec->size == 0) {
        return 0;
    }
    vec->size--;
    return vec->data[vec->size];
}

void vec_int_delete(vec_int* vec) {
    free(vec->data);
    free(vec);
}

void print_array(vec_int* vec) {
    printf("[");
    char end[2] = ", ";
    for (int i = 0; i < vec->size; i++) {
        if (i >= vec->size - 1) {
            end[0] = '\0';
        }
        printf("%d%s", vec->data[i], end);
    }
    printf("]\n");
}

int reallocs() {
    vec_int* vec = vec_int_new();
    vec_int_push(vec, 1);
    vec_int_push(vec, 2);
    vec_int_push(vec, 3);
    vec_int_push(vec, 4);
    print_array(vec);
    printf("%d\n", vec_int_pop(vec));
    print_array(vec);
    printf("%d\n", vec_int_pop(vec));
    print_array(vec);
    printf("%d\n", vec_int_pop(vec));
    print_array(vec);
    printf("%d\n", vec_int_pop(vec));
    print_array(vec);
    printf("%d\n", vec_int_pop(vec));
    print_array(vec);

    vec_int_delete(vec);

    return 0;
}