#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Routine for handling captured signals
static void captura(int sinal) {
    if (sinal == SIGINT)
        printf("Recebido o sinal SIGINT.\n");
    if (sinal == SIGTERM)
        printf("Recebido o sinal SIGTERM.\n");
    printf("Pretendo continuar executando!!!\n");
}

int main() {
    int i;
    
    // Capture SIGINT and SIGTERM signals
    if ((signal(SIGINT, captura) == SIG_ERR) || (signal(SIGTERM, captura) == SIG_ERR)) {
        printf("Erro ao instalar o tratador dos sinais.\n");
        exit(1);
    }

    i = 1; // Added missing semicolon

    while (1) { // Infinite loop
        printf("Estou vivo [%d].\n", i++);
        usleep(1000000); // Sleep for 1 second
    }

    return 0; // Optional return statement for main
}   