#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <uchar.h>
#include <stdbool.h>
#include <stdarg.h>
#include "print.h"

struct errormsg {
    char format[100];
    char *arguments[10];
    struct errormsg *next;
};

struct errormsg *errormsg_head = NULL;

struct foo {
    int large[10000];
};

struct bar {
    int a;
};

struct lazy {
    int *data;
    size_t len;
    size_t func_cap;
    size_t func_len;
    int (*funcs[])(int);
};

struct lazy *map(struct lazy *seq, int (*f)(int)) {
    if (seq->func_len == seq->func_cap) {
        seq->func_cap = seq->func_cap ? seq->func_cap * 2 : 2;
        seq = realloc(seq, sizeof(struct lazy) + seq->func_cap * sizeof(int (*)(int)));
        if (!seq) {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }
    seq->funcs[seq->func_len++] = f;
    return seq;
}

void foreach(struct lazy *seq, void (*f)(int)) {
    for (size_t i = 0; i < seq->len; ++i) {
        for (size_t j = 0; j < seq->func_len; ++j) {
            seq->data[i] = seq->funcs[j](seq->data[i]);
        }
        f(seq->data[i]);
    }
    seq->func_len = 0;
}

int square(int n) {
    return n * n;
}

int plusone(int n) {
    return n + 1;
}

int funcptr() {
    struct lazy *seq = malloc(sizeof(struct lazy) + 10 * sizeof(int));
    if (!seq) {
        perror("Failed to allocate memory for lazy structure");
        return 1;
    }

    seq->data = malloc(10 * sizeof(int));
    if (!seq->data) {
        perror("Failed to allocate memory for data");
        free(seq);
        return 1;
    }

    seq->len = 10;
    seq->func_cap = 2;
    seq->func_len = 0;

    for (int i = 0; i < 10; ++i) {
        seq->data[i] = i;
    }

    seq = map(map(seq, square), plusone);
    foreach(seq, print1ds);
    printf("\n");

    free(seq->data);
    free(seq);

    return 0;
}

void varfunc(struct foo *f, ...) {
    va_list va;
    va_start(va, f);

    double d = va_arg(va, double);
    struct bar *bar_ptr = va_arg(va, struct bar *);

    printf("%d %f %d\n", f->large[9999], d, bar_ptr->a);

    va_end(va);
}

int vargs() {
    struct foo f = {.large[9999] = 9999};
    struct bar b = {.a = 10};

    varfunc(&f, 100.0, &b);

    return 0;
}

void formt_errormsg(const char *format, ...) {
    struct errormsg *errorp = malloc(sizeof(struct errormsg));
    if (!errorp) {
        perror("Failed to allocate memory for errormsg");
        return;
    }

    strcpy(errorp->format, format);

    va_list ap;
    va_start(ap, format);

    int i = 0;
    while (i < 10 && (errorp->arguments[i] = va_arg(ap, char *)) != NULL) {
        i++;
    }

    va_end(ap);
    errorp->next = NULL;

    if (!errormsg_head) {
        errormsg_head = errorp;
    } else {
        struct errormsg *temp = errormsg_head;
        while (temp->next) temp = temp->next;
        temp->next = errorp;
    }
}

void print_errormsg(void) {
    struct errormsg *errorp = errormsg_head;

    while (errorp) {
        printf("Format: %s\n", errorp->format);
        for (int i = 0; i < 10 && errorp->arguments[i]; i++) {
            printf("Argument %d: %s\n", i, errorp->arguments[i]);
        }
        errorp = errorp->next;
    }
}

void binary(double N) {
    printf("Octal: %o\n", *((unsigned int *)&N));
    printf("Hex: %x\n", *((unsigned int *)&N));
    printf("Binary: ");
    uint64_t *binary = (uint64_t *)&N;
    for (int i = 63; i >= 0; --i) {
        uint64_t mask = 1ULL << i;
        printf("%d", (*binary & mask) ? 1 : 0);
    }
    printf("\n");
}

void wchars() {
    setlocale(LC_ALL, "en_US.UTF-8");
    wchar_t wstr[] = L"ÄäÖöÜüẞß 日本国";
    wprintf(L"Wide string output: %ls\n", wstr);
}

void scansets() {
    setlocale(LC_ALL, "C");

    char a[100];
    char b[100];
    int c;

    printf("Enter input in the format 'string1#string2#integer': ");
    scanf("%[^#]#%[^#]#%d", a, b, &c);

    printf("a: %s\n", a);
    printf("b: %s\n", b);
    printf("c: %d\n", c);
}

void locales() {
    char *locale = setlocale(LC_ALL, "");
    printf("Locale: %s\n", locale);
}

void adv()
{
    //funcptr();
    // vargs();
    // errmsg();
    // bitfields();
    // volat();
    // locales();
    // wchars();
    // scansets();
    // Run various function demonstrations
    printf("Running funcptr:\n");
    funcptr();

    printf("\nRunning vargs:\n");
    vargs();

    printf("\nRunning errmsg:\n");
    formt_errormsg("Error: %s", "Invalid input", NULL);
    formt_errormsg("Error: %s %s", "File not found", "Permission denied", NULL);
    print_errormsg();

    printf("\nRunning binary conversion:\n");
    double N = 123.45;
    binary(N);

    printf("\nRunning wide character display:\n");
    wchars();

    printf("\nRunning scansets:\n");
    scansets();

    printf("\nRunning locales:\n");
    locales();
}
