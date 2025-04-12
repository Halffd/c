#include <stdio.h>
#include <math.h>

char* f="xy";
char e='Z';
int main(void) {
    // Compute exponentiation using math.pow (i.e., pow from <math.h>)
    double result1 = pow(1.0, 0.0);  // Expected to be 1.0
    double result2 = pow(0.0, 0.0);  // Many implementations return 1.0

    printf("pow(1.0, 0.0) = %f\n", result1);
    printf("pow(0.0, 0.0) = %f\n", result2);
    printf("%d %c %s %f %lf", 1/0,1/0,1/0,1/0,1/0);
    return 0;
}

