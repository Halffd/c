#include <stdio.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "lib.h"

#include <stdio.h>

struct m;

// Define a macro to select the appropriate sys_open function
#define _sys_open(a, b, c, ...) _Generic((c), \
    struct m *: sys_open2, \
    default: sys_open3)

// Define the main sys_open macro
#define sys_open(...) _sys_open(__VA_ARGS__, (struct m *)NULL)(__VA_ARGS__)

// Define the function for two arguments
void sys_open2(char *arg1, char *arg2) {
    puts(__func__);
}

// Define the function for three arguments
void sys_open3(char *arg1, char *arg2, char *arg3) {
    puts(__func__);
}

// Main function to demonstrate the usage
int funcs() {
    sys_open("one", "two");          // Calls sys_open2
    sys_open("one", "two", "three"); // Calls sys_open3
    return 0;
}
void c99_2(){
    funcs();
    return;
}