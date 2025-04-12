#define _GNU_SOURCE  // Needed for clone and its flags
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

// Your existing code continues here...
#define TAMANHO_PILHA 65536

sem_t mutex; // Create a mutex semaphore

void up(sem_t *sem) {
    sem_wait(sem);
}

void down(sem_t *sem) {
    sem_post(sem);
}

typedef struct {
    double saldo;
} Registro;

Registro registro;

Registro le_registro(int conta) {
    return registro;
}

void grava_registro(Registro reg, int conta) {
    registro = reg;
}

void atualiza_saldo(double valor, int conta) {
    Registro reg;
    up(&mutex); // Lock the semaphore

    printf("Iniciando operação [%.2f]\n", valor);
    reg = le_registro(conta);
    usleep(1000);
    reg.saldo += valor; // Update the balance
    grava_registro(reg, conta);

    printf("Terminada operação [%.2f]\n", valor);
    down(&mutex); // Unlock the semaphore
}

int funcaoDeposito(void *arg) {
    // Deposit 100.00
    atualiza_saldo(100, 0);
    return 0; // Add a return statement
}

int funcaoSaque(void *arg) {
    // Withdraw 200.00
    atualiza_saldo(-200, 0);
    return 0; // Add a return statement
}

int main() {
    void *pilha1, *pilha2;
    int pid1, pid2;

    // Initialize mutex with value 1 (only one thread in the critical section)
    sem_init(&mutex, 1, 1);

    registro.saldo = 500; // Initialize balance
    printf("Saldo antes das operações = %.2f\n", registro.saldo);

    // Allocate stack for deposit thread
    if ((pilha1 = malloc(TAMANHO_PILHA)) == NULL) {
        perror("Erro na alocação da pilha.");
        exit(1);
    }

    // Start deposit     thread
    pid1 = clone(funcaoDeposito,
                 pilha1 + TAMANHO_PILHA,
                 CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
                 NULL);

    // Allocate stack for withdrawal thread
    if ((pilha2 = malloc(TAMANHO_PILHA)) == NULL) {
        perror("Erro na alocação da pilha.");
        exit(1);
    }

    // Start withdrawal thread
    pid2 = clone(funcaoSaque,
                 pilha2 + TAMANHO_PILHA,
                 CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
                 NULL);

    // Wait for the operations to finish
    waitpid(pid1, 0, 0);
    waitpid(pid2, 0, 0);

    printf("Saldo depois das operações = %.2f\n", registro.saldo);

    // Clean up
    sem_destroy(&mutex); // Destroy the semaphore
    free(pilha1); // Free allocated memory
    free(pilha2); // Free allocated memory

    return 0; // Return from main
}