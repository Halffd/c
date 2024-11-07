#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <stdatomic.h>
#include <threads.h>

#define NUM_THREADS 4

long long factorial_part(int n) {
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Thread function
int thread_func(void* arg) {
    int n = *(int*)arg;
    long long* result = malloc(sizeof(long long));
    *result = factorial_part(n);
    return (int)(long long)result;  // Return the result as a pointer
}

int threads_factorial() {
    thrd_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    long long results[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i + 1; // Arguments to threads: 1 to 16
        thrd_create(&threads[i], thread_func, &thread_args[i]);
    }

    // Join threads and collect results
    for (int i = 0; i < NUM_THREADS; ++i) {
        long long* result;
        thrd_join(threads[i], (int*)&result);
        results[i] = *result;
        free(result);  // Free allocated memory
    }

    // Calculate the final factorial
    long long final_result = 1;
    for (int i = 0; i < NUM_THREADS; ++i) {
        final_result *= results[i];
    }

    printf("Factorial of 16 is: %lld\n", final_result);
    return 0;
}
void stdthr() {
    // Check thread support
    #ifdef __STDC_NO_THREADS__
    printf("Thread support: NO\n");
    #else
    printf("Thread support: YES\n");
    #endif

    // Check atomic support
    #ifdef __STDC_NO_ATOMIC__
    printf("Atomic support: NO\n");
    #else
    printf("Atomic support: YES\n");
    #endif

    // Max thread count (not directly available in standard C, so just a placeholder)
    // You can use system-specific APIs to get actual limits
    printf("Max number of threads: (system-dependent, not available in standard C)\n");
    
    // Additional information (speed and max size are typically system-dependent and not standardized)
    printf("Speed of threads: (system-dependent, not available in standard C)\n");
    printf("Max thread stack size: (system-dependent, not available in standard C)\n");
}

int c11() {
    //stdthr();
    threads_factorial();
    return 0;
}
#endif