#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

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
    stdthr();
    return 0;
}