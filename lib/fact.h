#include <stdio.h>

int fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

int mains() {
    int num = 5;
    int result = fact(num);
    printf("The factorial of %d is: %d\n", num, result);
    
    return 0;
}