#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int factorial_iterative(int n);
int factorial_recursive(int n);
int fibonacci_iterative(int n);
int fibonacci_recursive(int n);
// Global memo table
int *memo;

// Memoized recursive Fibonacci
int fibonacci_memo(int n) {
    // Check if already computed
    if (memo[n] != -1) {
        return memo[n];
    }
    
    // Base cases
    if (n <= 1) {
        memo[n] = n;
        return n;
    }
    
    // Calculate and store result
    memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    return memo[n];
}

// Wrapper function that initializes memo table
int fibonacci(int n) {
    // Initialize memo table with -1 (uncalculated)
    memo = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    
    int result = fibonacci_memo(n);
    
    // Clean up
    free(memo);
    return result;
}
// TRUE tail recursive factorial
int factorial_tail(int n, int accumulator) {
    if (n <= 1) return accumulator;
    return factorial_tail(n - 1, n * accumulator); // No pending operations after recursion
}


// Wrapper function with default accumulator
int factorial_optimized(int n) {
    return factorial_tail(n, 1);
}
int main() {
    int choice, n;
    const int v = 30;
    const int f = factorial_optimized(v);
    const int fib = fibonacci(v);
    printf("Tail factorial %d: %d\n", v, f);
    printf("Fibonaci %d: %d\n", v, fib);
    printf("\n=== ALGORITHM DEMONSTRATION ===\n");
    printf("1. Factorial (Iterative)\n");
    printf("2. Factorial (Recursive)\n");
    printf("3. Fibonacci (Iterative)\n");
    printf("4. Fibonacci (Recursive)\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    
    printf("Enter a number: ");
    scanf("%d", &n);
    
    switch(choice) {
        case 1:
            printf("\nFactorial of %d (iterative): %d\n", n, factorial_iterative(n));
            break;
        case 2:
            printf("\nFactorial of %d (recursive): %d\n", n, factorial_recursive(n));
            break;
        case 3:
            printf("\nFibonacci sequence (iterative) up to %d terms:\n", n);
            for(int i = 1; i <= n; i++) {
                printf("%d ", fibonacci_iterative(i));
            }
            printf("\n");
            break;
        case 4:
            printf("\nFibonacci sequence (recursive) up to %d terms:\n", n);
            for(int i = 1; i <= n; i++) {
                printf("%d ", fibonacci_recursive(i));
            }
            printf("\n");
            break;
        default:
            printf("\nInvalid choice!\n");
    }
    
    return 0;
}

// Iterative factorial implementation
int factorial_iterative(int n) {
    int result = 1;
    
    for(; n > 1; n--) {
        result = result * n;
    }
    
    return result;
}

// Recursive factorial implementation
int factorial_recursive(int n) {
    if(n <= 1) {
        return 1;
    } else {
        return n * factorial_recursive(n-1);
    }
}

// Iterative Fibonacci implementation
int fibonacci_iterative(int n) {
    if(n <= 0) return 0;
    if(n == 1) return 1;
    
    int a = 0;
    int b = 1;
    int result = 0;
    
    for(int i = 2; i <= n; i++) {
        result = a + b;
        a = b;
        b = result;
    }
    
    return result;
}

// Recursive Fibonacci implementation
int fibonacci_recursive(int n) {
    if(n <= 0) return 0;
    if(n == 1 || n == 2) return 1;
    
    return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}
