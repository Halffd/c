
//cálculo da sequência de Fibonacci com uso da recursividade.
#include <stdio.h>
#include <stdlib.h>

//protótipo de função Fibonacci
int fibonacci(int);

int main()
{
    int n, i;
    printf("Digite a quantidade de termos da série: ");
    scanf("%d", &n);
    printf("Sequência de Fibonacci é: \n");
    for(i=0; i < n; i++)
        printf("%d ", fibonacci(i+1));
    return 0;
}

//função recursiva de Fibonacci
int fibonacci(int num)
{
    if (num == 1 || num == 2)
        return 1;
    else
        return fibonacci(num - 1) + fibonacci(num - 2);
}