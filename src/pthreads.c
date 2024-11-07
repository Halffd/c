#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <stdatomic.h>
#define _POSIX_C_SOURCE 200112L // Or a suitable version
#include <unistd.h>
#include <semaphore.h>
#ifndef PTHREAD_THREADS_MAX
#define PTHREAD_THREADS_MAX 1024 // or any other reasonable number
#endif
#define MAXTHREADS 100

void *funcaoC(void *);
void *funcaoCJ(void *);
sem_t semaphore;
pthread_mutex_t meuMutex = PTHREAD_MUTEX_INITIALIZER;
int contador = 0; // Corrected declaration of contador

#define THREADS_TO_CREATE 92233720

int t_fking() {
    int IdentificacaoDoProcesso; /* PID – Identificação do processo junto ao S.O. */
    
    IdentificacaoDoProcesso = fork();

    if (IdentificacaoDoProcesso == 0) { /* Este é o processo Filho */
        printf("Eu sou o processo filho: PID = %d \n", getpid());
    } else if (IdentificacaoDoProcesso > 0) { /* Este é o processo pai */
        printf("Eu sou o processo pai com PID = %d, o PID do filho é = %d \n", getpid(), IdentificacaoDoProcesso);
    } else {
        printf("Erro ao tentar criar processo filho\n");
        perror("fork");
        exit(1);
    }

    exit(0);
}
void *thread_functionN(void *arg) {
    return NULL;
}

int max_threads() {
    pthread_t threads[THREADS_TO_CREATE];
    int i;

    for (i = 0; i < THREADS_TO_CREATE; i++) {
        if (pthread_create(&threads[i], NULL, thread_functionN, NULL) != 0) {
            printf("Failed to create thread %d\n", i);
            break; // Exit on failure
        }
    }

    printf("Created %d threads.\n", i);
    
    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL); // Wait for threads to finish
    }

    return 0;
}
int p_threads_joins() {
    pthread_t identificacaoDaThread[MAXTHREADS];
    int i, j;

    // Create threads
    for (i = 0; i < MAXTHREADS; i++) {
        if (pthread_create(&identificacaoDaThread[i], NULL, funcaoCJ, NULL) != 0) {
            fprintf(stderr, "Falha na criação do thread %d\n", i);
            return 1; // Exit if thread creation fails
        }
    }

    // Wait for threads to complete
    for (j = 0; j < MAXTHREADS; j++) {
        pthread_join(identificacaoDaThread[j], NULL);
    }

    // Print the final value of the counter
    printf("Valor final do contador: %d \n", contador);
    return 0; // Return 0 at the end of main
}

void *funcaoCJ(void *meuPTR) {
    pthread_mutex_lock(&meuMutex); // Lock the mutex before modifying the shared variable
    printf("Numero desta thread: %ld \n", (long)pthread_self());

    contador++;
    printf(" %d ", contador);
    pthread_mutex_unlock(&meuMutex); // Unlock the mutex after modification

    return NULL; // Return NULL to match the expected return type
}
int mutexes() {
    int retorno1, retorno2;
    pthread_t threadUm, threadDois;

    // Create independent threads. Each will run funcaoC.
    if ((retorno1 = pthread_create(&threadUm, NULL, funcaoC, NULL))) {
        printf("Falha na criação do thread: %d \n", retorno1);
    }

    if ((retorno2 = pthread_create(&threadDois, NULL, funcaoC, NULL))) {
        printf("Falha na criação do thread: %d \n", retorno2);
    }

    // Wait until the threads finish before continuing in main.
    pthread_join(threadUm, NULL);
    pthread_join(threadDois, NULL);

    return 0; // Use return instead of exit(0)
}

void *funcaoC(void *arg) {
    pthread_mutex_lock(&meuMutex); // Lock the mutex before modifying the shared variable
    contador++;
    printf("Valor do contador: %d \n", contador);
    pthread_mutex_unlock(&meuMutex); // Unlock the mutex after modification
    return NULL; // Return NULL to match the expected return type
}
void* thread_function(void* arg) {
    // Wait (decrement the semaphore)
    sem_wait(&semaphore);

    // Critical section
    printf("Thread %ld in critical section\n", (long)arg);
    sleep(1); // Simulate work

    // Signal (increment the semaphore)
    sem_post(&semaphore);
    return NULL;
}

int semaphores() {
    pthread_t threads[5];
    long thread_args[5]; // Store thread indices

    // Initialize the semaphore with a value of 1 (binary semaphore)
    sem_init(&semaphore, 0, 1);

    for (long i = 0; i < 5; i++) {
        thread_args[i] = i; // Assign the index to the array
        pthread_create(&threads[i], NULL, thread_function, (void*)&thread_args[i]); // Pass the address
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);
    return 0;
}
// Function that prints a message
void* imprime_mensagem(void* ptr) {
    char* mensagem = (char*)ptr;
    printf("%s\n", mensagem); // Print the message
    return NULL; // Return NULL to match the expected return type of the thread function
}

// Function that runs a thread to receive an integer
void* vpf(void* arg) {
    int* value = (int*)arg;  // Cast the void pointer to the appropriate type
    printf("Thread received value: %d\n", *value);
    return NULL;  // Return NULL since the function returns void*
}

int pthread_vptr() {
    pthread_t thread;
    int value = 42;

    // Create a thread that runs the function f
    if (pthread_create(&thread, NULL, vpf, (void*)&value) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);
    return 0;
}

int pthread2() {
    pthread_t threadUm, threadDois;
    char *mensagem1 = "threadUm: Frase 1";
    char *mensagem2 = "threadDois: Frase 2";
    int retorno1, retorno2;

    // Create independent threads, each executing the function
    retorno1 = pthread_create(&threadUm, NULL, imprime_mensagem, (void *)mensagem1);
    retorno2 = pthread_create(&threadDois, NULL, imprime_mensagem, (void *)mensagem2);

    // Wait until the threads finish before continuing in main
    pthread_join(threadUm, NULL);
    pthread_join(threadDois, NULL);

    printf("A threadUm retornou: %d \n", retorno1);
    printf("A threadDois retornou: %d \n", retorno2);

    return 0; // Use return 0 instead of exit(0)
}
void display_thread_info() {
    // Check for thread support
    #ifdef __STDC_NO_THREADS__
    printf("Thread support: NO\n");
    #else
    printf("Thread support: YES\n");
    #endif

    // Check for atomic support
    #ifdef __STDC_NO_ATOMIC__
    printf("Atomic support: NO\n");
    #else
    printf("Atomic support: YES\n");
    #endif

    // Maximum number of threads (using PTHREAD_THREADS_MAX)
    printf("Max number of threads (from PTHREAD_THREADS_MAX): %d\n", PTHREAD_THREADS_MAX);

    // Maximum stack size for threads (system-dependent)
    size_t stack_size;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stack_size);
    pthread_attr_destroy(&attr);
    printf("Max thread stack size: %zu bytes\n", stack_size);

    // Speed of threads is not directly measurable in a standard way
    printf("Speed of threads: (system-dependent; performance can vary)\n");
}
int sleeps() {
    printf("Starting...\n");
    sleep(2);  // Delay for 2 seconds
    printf("2 seconds later...\n");
    sleep(3);  // Delay for 3 seconds
    printf("3 seconds later...\n");
    return 0;
}

// Main function to call other functions
int pthr() {
    // Uncomment one of the following lines to test different functionalities
    semaphores();
    //pthread_vptr();
    //pthread2();
    //sleeps();
    // pthr(); // Assuming pthr() is defined somewhere else if needed

    //display_thread_info(); // Display thread info
    //mutexes();
     p_threads_joins();
//    max_threads();
    t_fking();
    return 0;
}