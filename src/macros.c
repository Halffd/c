#include <stdio.h>

//#pragma once
#include "lib.h"

#include <limits.h>
#include <float.h>

#include <stdint.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c) (MAX(a, MAX(b, c)))


#define STRINGIFY(x) #x
#define STRINGIFY_EXPAND(x) STRINGIFY(x)

#define FRUITS(func) \
 func(banana) \
 func(apple) \
 func(orange) \
 func(grape)

#define GENERATE_ENUM(name) name,
#define GENERATE_CASE(name) case name: return STRINGIFY_EXPAND(name);

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define LOG_ERROR(...) fprintf(stderr, __FILE__ ":" STR(__LINE__) ": " __VA_ARGS__)

#if defined(ONE) || defined(ZERO)
printf("sir please do not define ONE or ZERO")
#else
#define ONE 1
#define ZERO 0
#endif
#ifndef UNICODE
#define UNICODE
#endif 

#define func_A(X) func_B(X, 0, 0)


typedef enum {
 FRUITS(GENERATE_ENUM)
} fruit_t;

const char* fruit_to_string(fruit_t fruit) {
 switch (fruit) {
 FRUITS(GENERATE_CASE)
 default: return "unknown";
 }
}
int intmax(void)
{
 errno = 0;

 intmax_t first = 0, second = 0, third = 0;
 int parsed = scanf("%jd", &first) + scanf("%jd", &second) + scanf("%jd", &third);

 if (parsed == 3)
 printf("maximum: %jd\n", MAX3(first, second, third));
 else if (errno)
 printf("error");
 else if (feof(stdin))
 printf("error: end of file");
 else
 printf("error: only parsed %d/3 numbers", parsed);

 return 0;
}
int foo(int *i) {
 #define i (*i)
 i = 5;
 #undef i
 return *i;
}
void func_B(int x, int y, int z)
{
    // Do something with x, y, and z
    if(!x){
        LOG_ERROR("xnull");
    }
    printf("x: %d, y: %d, z: %d\n", x, y, z);
}
int flt() {
    
    char buffer[50];
    sprintf(buffer, "%f", FLT_MIN);
    printf("FLT_MIN: %s\n", buffer);

    
    char buffer2[50000];
    sprintf(buffer2, "%f", FLT_EPSILON);
    printf("FLT_MIN: %s\n", buffer);
    printf("FLOAT:\n");
    printf("Size: %zu bytes\n", sizeof(float));
    printf("Minimum value: %s\n", buffer);
    printf("Maximum value: %f\n", FLT_MAX);
    printf("Smallest positive value: %s\n", buffer2);
    printf("Number of decimal digits of precision: %d\n\n", FLT_DIG);

    printf("DOUBLE:\n");
    printf("Size: %zu bytes\n", sizeof(double));
    printf("Minimum value: %f\n", DBL_MIN);
    printf("Maximum value: %f\n", DBL_MAX);
    printf("Smallest positive value: %f\n", DBL_EPSILON);
    printf("Number of decimal digits of precision: %d\n", DBL_DIG);

    float floatValue = 3.14159f;
    double doubleValue = 3.141592653589793;

    char floatFormat[10];
    char doubleFormat[10];

    snprintf(floatFormat, sizeof(floatFormat), "%%.%dg", FLT_MANT_DIG - FLT_MIN_EXP);
    snprintf(doubleFormat, sizeof(doubleFormat), "%%.%dlg", DBL_MANT_DIG - DBL_MIN_EXP);

    printf("Float value: ");
    printf(floatFormat, floatValue);
    printf("\n");

    printf("Double value: ");
    printf(doubleFormat, doubleValue);
    printf("\n");

    return 0;
}
int defn()
{
    return intmax();
}
int frt(){
    // func_A(10);
    //func_A(0);
    fruit_t myFruit = banana;
    const char* fruitString = fruit_to_string(myFruit);
    const char* fruit = fruit_to_string(grape);
    printf("My fruit is: %s\n", fruitString);
    printf("My fruit is: %s\n", fruit);
    int var = 0;
    int ceiling = 2;
    if (var < ceiling)
    {
        var += ONE;
    }
    else
    {
        var += ZERO;
    }
    
    #undef ZERO
    #undef ONE
    printf("zero/one:%d",var);
    return 0;
}