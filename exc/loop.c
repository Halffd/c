#include <stdio.h>
#include <time.h>

// O(n³) Triple nested loop
void triple_loop(int n) {
    clock_t start = clock();
    int a = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n-1; k++) {
                a = a * (i + j);  // Core operation
            }
        }
    }
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("O(n³) Triple nested loop\n");
    printf("Result: %d\tTime: %.6f s\n\n", a, duration);
}

// O(1) Simple condition
void simple_condition(int a, int b) {
    clock_t start = clock();
    if(a < b) {
        a++;
    }
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("O(1) Simple condition\n");
    printf("Result: %d\t\tTime: %.6f s\n\n", a, duration);
}

// O(n) Conditional with loop
void conditional_with_loop(int a, int b, int n) {
    clock_t start = clock();
    if(a < b) {
        a++;
    } else {
        for(int i = 1; i < n; i++) {
            a *= i;
        }
    }
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("O(n) Conditional with loop\n");
    printf("Result: %d\t\tTime: %.6f s\n\n", a, duration);
}

// O(n) While loop
void while_loop(int n) {
    clock_t start = clock();
    int a = 1;
    int i = 2, j = 3;
    while(a < n) {
        a = a * (i + j);
    }
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("O(n) While loop\n");
    printf("Result: %d\t\tTime: %.6f s\n\n", a, duration);
}

// O(n) Function call
int sum(int a, int b, int n) {
    clock_t start = clock();
    for(int i = 0; i < n; i++) {
        a++;
    }
    double duration = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("O(n) Function call\n");
    printf("Result: %d\t\tTime: %.6f s\n\n", a + b, duration);
    return a + b;
}

int main() {
    // Test different complexity cases
    triple_loop(300000);          // O(n³)
    simple_condition(3, 300000);  // O(1)
    conditional_with_loop(300000, 3, 30);  // O(n)
    while_loop(300000);         // O(n)
    sum(0, 0, 300000);      // O(n)

    return 0;
}
