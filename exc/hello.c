#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("hello: %d", argc);
    
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    return 0;
}
