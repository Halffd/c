#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
} obj;

int objinit(obj *o, int value)
{
    if (value < 0)
    {
        return 1; // Indicate initialization failure
    }

    o->value = value;
    return 0; // Indicate successful initialization
}

void dispatch_some_error()
{
    printf("An error occurred!\n");
}

int testingfree()
{
    obj *o = malloc(sizeof(obj));
    if (o == NULL)
    {
        printf("Failed to allocate memory!\n");
        return 1;
    }

    const int r = objinit(o, -1);
    if (r)
    {
        free(o);
        dispatch_some_error();
       // return 1;
    }


    free(o);
    printf("Object value: %p\n", &o);

    return 0;
}