#include <stdio.h>
#include <stdlib.h>
#include "print.h"
#include "lib.h"

int arrptrtest()
{
    // Step 1: Allocate memory for integers
    int *arr = (int *)calloc(12, sizeof(int));

    // Check if allocation was successful
    if (arr == NULL)
    {
        perror("Failed to allocate memory");
        return 1;
    }

    // Step 2: Initialize the array
    arr[0] = 2;
    arr[1] = 3;
    arr[2] = 4;
    arr[3] = 5;

    int *p = (arr + 2);

    print1p(arr);
    print1p(p);
    print1d(*p);
    print1d(*arr + 15);
    print1d(sizeof(arr[0]));
    print1d(sizeof(arr) / sizeof(arr[0]));
    print1d(1234567);
    int **r = &p;
    print1d(**r);
    print1p(r);
    print1d(**r - *arr);
    print1d(&arr[0] - *r);
    return 0;
}
int arrest()
{
    static int i, NUM[15];

    // lendo os valores

    for (i = 0; i < 15; i++)
    {

        printf("Informe um numero: \n");

        scanf("%d", &NUM[i]);
    }

    // imprimindo os valores

    for (i = 0; i < 15; i++)
    {

        printf("Numero: %d \n", NUM[i]);
    }
}
int max(int, int);
int maxtst()
{
    print1d(11111111);
    //setlocale(LC_ALL, "pt_BR.UTF-8"); // Set locale to UTF-8
    float c = -10.5251295f;
    c = (int) c;
    int a = (int) c;
    a |= (int) -1210530.3495;
    int b = 0xFFFF;
    b &= 12;
    b <<= 4;
    b /= -3.251;
    b = (int)b;
    b ^= -5;
    b >>= 0b1010;
    b += 0712;
    b &= 0777777;
    b |= !0b010;
    b -= !0x111;
    b += !010000;
    b != (int) 2.95000001;
    print("dcd", a, ' ', b);
    int ret;

    ret = max(a, b);
    print1d(222222222);
    print("sd", "O valor maximo e: ", ret);

    return 0;
}
/* função retornando o máximo entre dois números */
int max(int num1, int num2)
{
    int resultado;
    if (num1 > num2)
        resultado = num1;
    else
        resultado = num2;
    return resultado;
}
int est(int argc, char *argv[])
{
    printi(3, 4, argc, -8);
    prints("sds", "\n", " ", "est:", argc, argv[0]);
    // return arrptrtest();
    // arrest();
    maxtst();
}