#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO 10

void bolha(int *v, int print_steps) {
    int troca = 1;
    int i = 0;
    int aux;
    int passes = 0;
    int comparisons = 0;
    int swaps = 0;
    
    printf("Initial array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n\n");
    
    clock_t start = clock();
    
    while (troca) {
        passes++;
        troca = 0;
        while (i < TAMANHO - 1) {
            comparisons++;
            if (print_steps) printf("Comparing v[%d]=%d and v[%d]=%d\n", i, v[i], i+1, v[i+1]);
            
            if (v[i] > v[i+1]) {
                aux = v[i];
                v[i] = v[i+1];
                v[i+1] = aux;
                swaps++;
                troca = 1;
                
                if (print_steps) {
                    printf("SWAP! Array now: ");
                    for (int j = 0; j < TAMANHO; j++) {
                        printf("%d ", v[j]);
                    }
                    printf("\n");
                }
            }
            i++;
        }
        
        if (print_steps && passes > 0) {
            printf("\n--- End of pass %d ---\n", passes);
            printf("Current array: ");
            for (int j = 0; j < TAMANHO; j++) {
                printf("%d ", v[j]);
            }
            printf("\n\n");
        }
        
        i = 0;
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n----- FINAL STATS -----\n");
    printf("Sorted array: ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", v[j]);
    }
    printf("\n");
    printf("Total passes: %d\n", passes);
    printf("Total comparisons: %d\n", comparisons);
    printf("Total swaps: %d\n", swaps);
    printf("Time spent: %.6f seconds\n", time_spent);
    printf("----------------------\n\n");
}

int main() {
    int sorted[TAMANHO] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int unsorted[TAMANHO] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int half_sorted[TAMANHO] = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6};
    
    int test_case[TAMANHO];
    
    printf("===== FULLY SORTED ARRAY TEST =====\n");
    memcpy(test_case, sorted, sizeof(sorted));
    bolha(test_case, 1);
    
    printf("===== FULLY UNSORTED (REVERSE) ARRAY TEST =====\n");
    memcpy(test_case, unsorted, sizeof(unsorted));
    bolha(test_case, 1);
    
    printf("===== HALF SORTED ARRAY TEST =====\n");
    memcpy(test_case, half_sorted, sizeof(half_sorted));
    bolha(test_case, 1);
    
    // Bonus: Random array test
    printf("===== RANDOM ARRAY TEST =====\n");
    srand(time(NULL));
    for (int i = 0; i < TAMANHO; i++) {
        test_case[i] = rand() % 100;
    }
    bolha(test_case, 1);
    
    return 0;
}