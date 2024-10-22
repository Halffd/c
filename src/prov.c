#include <stdio.h>
#include "lib.h"
#include <limits.h>


int prov(int argc, char const *argv[])
{
    
    // printf("C v%d", __STDC_VERSION__);
    char letra;

    int num;

    printf("Entre com uma letra e um inteiro:\n");

    // scanf("%c %d", &letra, &num);

    // printf("Você informou a letra %c e o inteiro %d.\n", letra, num);
    int c = 0;
    int ind, cont;

    for (ind = 15; ind >= 4; ind--)
    {
        // Código a ser executado em cada iteração do loop
        c++;
        cont--;
    }
    printf("%d", c);
    int a = sizeof(float);
    size_t b = a * CHAR_BIT;
    printf("\n\nf: %d %d\n\n", a, b);
    char nome[20];

    char sexo;

    printf("Qual é o seu nome?");

    scanf(nome);

    printf("Qual é o seu sexo? (f/m) ");

    scanf(&sexo);

    if (sexo == 'f' && sexo == 'F')

        printf("Você é do sexo feminino. ");

    else

        if (sexo == 'm' && sexo == 'M')

        printf("Você é do sexo masculino. ");

    else

        printf("Você digitou um valor de sexo invalido ");

    return 0;
}
