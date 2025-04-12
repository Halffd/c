#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void reverse_int(int *n) {
    int sum = 0;

    while (*n) {
        sum = sum * 10 + (*n) % 10;
        *n /= 10;
    }

    *n = sum;
}

void reverse(char *s) {
    size_t len = strlen(s);
    size_t i, j;

    for (i = 0, j = len - 1; i < j; ++i, --j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

int rev() {
    char str[] = "abcde";
    char *c = (char *)malloc(strlen(str) + 1);
    strcpy(c, str);

    printf("strrev-pre : %s\n", c);
    reverse(c);
    printf("strrev-post: %s\n", c);

    free(c);

    int i = 1234567;
    printf("mathrev-pre : %d\n", i);
    reverse_int(&i);
    printf("mathrev-post: %d\n", i);

    return 0;
}