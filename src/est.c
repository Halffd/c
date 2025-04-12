#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif
#include "print.h"
#include "lib.h"
#define LEN 150

#define WIDTH 256
#define HEIGHT 256

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
    // setlocale(LC_ALL, "pt_BR.UTF-8"); // Set locale to UTF-8
    float c = -10.5251295f;
    c = (int)c;
    int a = (int)c;
    a |= (int)-1210530.3495;
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
    b != (int)2.95000001;
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

int timelib()
{

    time_t seg;

    seg = time(NULL);

    print("sd", "O numero de horas desde 1º de janeiro de 1970 eh", (int) seg / 3600);
    {

        time_t minha_hora;

        minha_hora = time(NULL);

         print1s(ctime(&minha_hora));
    }

    {
        char buf[LEN];

        time_t curtime;

        struct tm *loc_time;

        // obtém hora corrente do sistema

        curtime = time(NULL);

        // converte para a hora local

        loc_time = localtime(&curtime);

        // mostra hora e data no formato-padrão
        print1s(asctime(loc_time));

        strftime(buf, LEN, "Hoje eh %A, %b %d.", loc_time);
        print1s(buf);

        strftime(buf, LEN, "A hora eh %I : %M : %S %p.", loc_time);

        print1s(buf);
    }
    {

        time_t start, end;

        volatile long unsigned contador;

        start = time(NULL);

        for (contador = 0; contador < 500000000; contador++); /* Não executa nada */

        end = time(NULL);

        print("sfs", "O loop for usa ", difftime(end, start), " segundos");
    }
    return 0;
}
void saida(){
 // Exemplo de formatação de strings
    int num = -42;
    float pi = 3.14159;
    char letter = 'A';
    char *str = "Hello, World!";
    
    printf("Character: %c\n", letter);
    printf("Integer with sign: %d\n", num);
    printf("Float: %f\n", pi);
    printf("Scientific notation (lowercase): %e\n", pi);
    printf("String: %s\n", str);
    printf("Hexadecimal (lowercase): %x\n", 255);
    printf("Hexadecimal (uppercase): %X\n", 255);
    printf("Percentage: 100%% complete\n");

    // Exemplo de códigos especiais
    printf("This is line one.\nThis is line two.\n");
    printf("Column1\tColumn2\n");
    printf("Hello\bWorld\n");
    printf("Hello\rWorld\n");
    printf("Quote: \"This is a quote.\"\n");
    printf("Backslash: \\\n");

    char ch1,ch2,ch3;

   // ch1=getch(); //Não exibe o caractere na tela
#ifdef _WIN32
    ch2=getche(); //Exibe o caractere na tela
#else
    ch2-'0';
#endif
    ch3=getchar(); //Exibe o caractere na tela e aguarda Enter para armazenar na variável ch3
    char ch4[100]; // Buffer to hold the input string
    printf("Enter a string: ");
    
    // Using fgets to safely read a string
    if (fgets(ch4, sizeof(ch4), stdin) != NULL) {
        printf("You entered: %s", ch4);
    }
    char s[55];
#ifdef _WIN32
    gets(s);
#endif
    printf("%c %c %c %s",ch1,ch2,ch3, s);
}
void create_rgb_binary(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to create binary file");
        return;
    }

    // Write pixel data (RGB format)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            unsigned char r = (unsigned char)(255.0 * x / WIDTH); // Gradient from black to red
            unsigned char g = (unsigned char)(255.0 * y / HEIGHT); // Gradient from black to green
            unsigned char b = 0; // No blue for this gradient

            // Write RGB values to binary file
            fwrite(&r, sizeof(unsigned char), 1, file);
            fwrite(&g, sizeof(unsigned char), 1, file);
            fwrite(&b, sizeof(unsigned char), 1, file);
        }
    }

    fclose(file);
    printf("Custom binary file created: %s\n", filename);
}
void read_rgb_binary(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open binary file");
        return;
    }

    // Allocate memory for pixel data
    unsigned char (*pixelData)[3] = malloc(HEIGHT * WIDTH * 3 * sizeof(unsigned char));
    if (pixelData == NULL) {
        perror("Unable to allocate memory for pixel data");
        fclose(file);
        return;
    }

    // Read pixel data
    size_t bytesRead = fread(pixelData, sizeof(unsigned char), WIDTH * HEIGHT * 3, file);
    if (bytesRead != WIDTH * HEIGHT * 3) {
        printf("Error reading pixel data.\n");
    }

    // Print some pixel values (first 10 pixels)
    for (int y = 0; y < 1; y++) { // Only first row for simplicity
        for (int x = 0; x < 10; x++) {
            unsigned char r = pixelData[y * WIDTH + x][0];      // Red
            unsigned char g = pixelData[y * WIDTH + x][1];      // Green
            unsigned char b = pixelData[y * WIDTH + x][2];      // Blue
            printf("Pixel (%d, %d) - R: %d, G: %d, B: %d\n", x, y, r, g, b);
        }
    }

    free(pixelData);
    fclose(file);
}
int est(int argc, char *argv[])
{
    printi(3, 4, argc, -8);
    prints("sds", "\n", " ", "est:", argc, argv[0]);
    // return arrptrtest();
    // arrest();
    // maxtst();
    //timelib();
    create_rgb_binary("gradient.rgb");
    read_rgb_binary("gradient.rgb");
    saida();
}