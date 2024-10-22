#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>
#include <uchar.h>
#include <limits.h>
#include "lib.h"
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"

struct errormsg
{
    char format[100];
    char *arguments[10];
    struct errormsg *next;
};

struct errormsg *errormsg_head = NULL;
#include <stdarg.h>
#include <stdio.h>

struct foo
{
    int large[10000];
};

struct bar
{
    int a;
};

#include <stdio.h>
#include <stdlib.h>

struct lazy
{
    int *data;
    size_t len;
    size_t func_cap;
    size_t func_len;
    int (*funcs[])(int);
};

struct lazy *map(struct lazy *seq, int (*f)(int))
{
    if (seq->func_len == seq->func_cap)
    {
        seq->func_cap *= 2;
        seq = realloc(seq, sizeof(struct lazy) + seq->func_cap * sizeof(int (*)(int)));
    }
    seq->funcs[seq->func_len++] = f;
    return seq;
}

void foreach (struct lazy *seq, void (*f)(int))
{
    for (size_t i = 0; i < seq->len; ++i)
    {
        for (size_t j = 0; j < seq->func_len; ++j)
        {
            seq->data[i] = seq->funcs[j](seq->data[i]);
        }
        f(seq->data[i]);
    }
    seq->func_len = 0;
}

int square(int n)
{
    return n * n;
}

int plusone(int n)
{
    return n + 1;
}

int funcptr()
{
    struct lazy *seq = malloc(sizeof(struct lazy));
    seq->data = malloc(10 * sizeof(int));
    seq->len = 10;
    seq->func_cap = 0;
    seq->func_len = 0;

    for (int i = 0; i < 10; ++i)
    {
        seq->data[i] = i;
    }

    seq = map(map(seq, square), plusone);
    foreach (seq, print1ds)
        ;
    printf("\n");

    free(seq->data);
    free(seq);

    return 0;
}
void varfunc(struct foo *f, ...)
{
    va_list va;
    va_start(va, f); // Provide a null pointer as the second argument

    double d = va_arg(va, double);
    struct bar *bar_ptr = va_arg(va, struct bar *); // Rename the variable to avoid conflict

    printf("%d %f %d\n", f->large[9999], d, bar_ptr->a);

    va_end(va);
}

int vargs()
{
    struct foo f = {.large[9999] = 9999};
    struct bar b = {.a = 10};

    varfunc(&f, 100.0, &b);

    return 0;
}
void formt_errormsg(const char *format, ...)
{
    struct errormsg *errorp = errormsg_head;
    va_list ap;

    while (errorp != NULL)
        errorp = errorp->next;

    errorp = malloc(sizeof(struct errormsg));
    strcpy(errorp->format, format);

    va_start(ap, format);

    int i = 0;
    char *arg;
    while ((arg = va_arg(ap, char *)) != NULL && i < 10)
    {
        errorp->arguments[i] = arg;
        i++;
    }

    va_end(ap);

    errorp->next = NULL;

    if (errormsg_head == NULL)
    {
        errormsg_head = errorp;
    }
    else
    {
        struct errormsg *temp = errormsg_head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = errorp;
    }
}

void print_errormsg(void)
{
    struct errormsg *errorp = errormsg_head;

    while (errorp != NULL)
    {
        printf("Format: %s\n", errorp->format);
        printf("Arguments:\n");

        // Iterate through the arguments array until a NULL value is encountered
        for (int i = 0; i < 10 && errorp->arguments[i] != NULL; i++)
        {
            printf("%s\n", errorp->arguments[i]);
        }

        printf("\n");

        errorp = errorp->next;
    }
}
int errmsg()
{
    formt_errormsg("Error: %s", "Invalid input", NULL);
    formt_errormsg("Error: %s %s", "File not found", "Permission denied", NULL);

    print_errormsg();

    return 0;
}

#define MEMORY_POOL_SIZE 1024

static char memoryPool[MEMORY_POOL_SIZE];
static size_t nextFreeIndex = 0;

#define MEMORY_LIMIT (144000)

static char memory_buffer[MEMORY_LIMIT] = "";
static int memory_used = 0;

struct Player
{
    uint8_t name : 4;   // 4-bit field for the name
    uint8_t image : 3;  // 3-bit field for the image
    uint8_t status : 1; // 1-bit field for the status
};

int bitfields()
{
    struct Player player;

    player.name = 6;   // Set name to 6
    player.image = 2;  // Set image to 2
    player.status = 1; // Set status to active

    printf("Name: %u\n", player.name);
    printf("Image: %u\n", player.image);
    printf("Status: %u\n", player.status);

    return 0;
}
static void *memorize(int size)
{
    if (memory_used + size >= MEMORY_LIMIT)
    {
        exit(EXIT_FAILURE);
    }
    void *allocated_memory = (void *)&memory_buffer[memory_used];
    memory_used += size;
    return allocated_memory;
}

int mems()
{
    // Example usage
    int *dynamic_array = (int *)memorize(5 * sizeof(int));

    if (dynamic_array != NULL)
    {
        // Use the allocated memory
        for (int i = 0; i < 5; ++i)
        {
            dynamic_array[i] = i;
        }

        // Print the values
        for (int i = 0; i < 5; ++i)
        {
            printf("%d ", dynamic_array[i]);
        }
        printf("\n");
    }

    return 0;
}
void *my_malloc(size_t size)
{
    if (nextFreeIndex + size > MEMORY_POOL_SIZE)
    {
        // Out of memory
        return NULL;
    }

    void *allocatedMemory = &memoryPool[nextFreeIndex];
    nextFreeIndex += size;

    return allocatedMemory;
}
void my_free(void *ptr)
{
    asm volatile(
        "mov %[ptr], %%eax\n"
        "mov %%eax, %%edi\n"
        "jmp free_memory\n"
        "free_memory:\n"
        "xor %%eax, %%eax\n"
        "mov %%eax, (%%edi)\n"
        :
        : [ptr] "m"(ptr)
        : "%eax", "%edi");
}

int allc()
{
    // Example usage
    int *dynamicArray = (int *)my_malloc(5 * sizeof(int));

    if (dynamicArray != NULL)
    {
        // Use the allocated memory
        for (int i = 0; i < 5; ++i)
        {
            dynamicArray[i] = i;
            printf("%d", dynamicArray[i]);
        }

        my_free(dynamicArray);
    }

    return 0;
}
void binary()
{
    double N;

    printf("Please Enter A Positive Digit: ");
    scanf("%lf", &N);

    printf("Octal: %o\n", *((unsigned int *)&N));
    printf("Hex: %x\n", *((unsigned int *)&N));
    printf("Binary: ");

    for (int i = sizeof(N) * 8 - 1; i >= 0; --i)
    {
        // printf("%u", (N >> i) & 1);
    }
    // binary(N);
    double num = N;
    uint64_t *binary = (uint64_t *)&num;
    for (int i = 63; i >= 0; --i)
    {
        uint64_t mask = 1ULL << i;
        printf("%d", (*binary & mask) ? 1 : 0);
    }
}
void wchars()
{
    // システム既定のロケールに設定
    setlocale(LC_ALL, "en_US.UTF-8"); // Set locale to UTF-8
    fprintf(f, "wchars\n");
    // setlocale(LC_ALL, "ja_JP.UTF-8");
    fwprintf(f, L"%ls|%ls\n", L"ÄäÖöÜüẞß", L"кoшкa 日本国");

    wchar_t wmoji1 = L'A';
    wchar_t wmoji2 = L'あ';
    wchar_t wstr[] = L"ABCあいう";

    printf("%zu\n", sizeof(wmoji1));
    printf("%zu\n", sizeof(wmoji2));
    printf("%zu\n", sizeof(wstr));

    size_t size = sizeof(const short unsigned int *);
    size_t size2 = sizeof(const short unsigned int);
    size_t size3 = sizeof(wchar_t);
    printf("Size of const short unsigned int*: %zu / %zu / %zu bytes\n", size, size2, size3);
    fwprintf(f, L"%ls\n", wstr);
    wprintf(L"%lc %ls", L'A', L"Hüe");
    char16_t c16 = u'あ';
    char32_t c32 = U'あ';

    char16_t str16[] = u"あいうえお";
    char32_t str32[] = U"あいうえお";

    // Print characters
    wprintf(L"Character 16b (wchar_t): %lc\n", (wint_t)c16);
    wprintf(L"Character 32b (wchar_t): %lc\n", (wint_t)c32);

    // Print strings
    wprintf(L"String 16b (wchar_t): %ls\n", (wchar_t *)str16);
    wprintf(L"String 32b (wchar_t): %ls\n", (wchar_t *)str32);

    char mc1[] = "あ";
    wchar_t wc1 = L'あ';

    // 全てのロケールでの一文字の最大バイト数 + 1を確保
    // 最後の+1はNULL文字用
    char mc2[MB_LEN_MAX + 1];
    wchar_t wc2;

    // マルチバイト文字をワイド文字に変換
    int len = mbtowc(&wc2, mc1, MB_CUR_MAX);
    if (len < 0)
    {
        fwprintf(f, L"マルチバイト文字からワイド文字への変換失敗\n");
    }
    else
    {
        fwprintf(f, L"%lc\n", wc2);
    }

    // ワイド文字をマルチバイト文字に変換
    len = wctomb(mc2, wc1);
    if (len < 0)
    {
        fwprintf(f, L"ワイド文字からマルチバイト文字への変換失敗\n");
    }
    else
    {
        // 文字の最後にNULL文字を追加
        mc2[len] = '\0';
        fwprintf(f, L"%s\n", mc1);
    }

    getchar();
}
void locales()
{
    char *locale = setlocale(LC_ALL, "");
    wint_t buffer;
    printf("%s\n", locale);
    while ((buffer = fgetwc(f)) != WEOF)
    {
        putwchar(buffer);
        printf("\n");
    }
    fclose(f);
}
static inline int ranN(register int seed)
{
    register int init = seed * ((1 << 27) + 31);
    return (init + 17) >> 4;
}
char *ret_char()
{
    static char str[] = "Hello!";
    return (str);
}
void vars()
{
    register int s = (int)time(0);
    srand(s);
    register int n;
    for (register int i = 1; i < rand(); i++)
    {

        puts(ret_char());
        printf("\n");
        do
        {
            s = rand();
            n = s / i;
            n = ranN(n);
            printf("%3d\n", n);
        } while (s < 1000);
    }
}
int variable_length_array(int size)
{
    // volatile so compiler won't optimize it away
    volatile int array[size];

    for (int i = 0; i < size; i++)
    {
        array[i] = i;
        printf("%d ", array[i]);
    }
}
void volat()
{

    volatile int x = 10;

    asm("movl $20,12(%rsp)");
    printf("x = %d\n\n", x);
    variable_length_array(2);
    volatile int i = 0;
    uintptr_t a;
    uintptr_t b;
    {
        int v[2] = {0, 0};
        a = (uintptr_t)&v[i];
    }
    {
        int v[2] = {0, 0};
        b = (uintptr_t)&v[i];
    }
    printf(
        "%ld == %ld %s",
        a,
        b,
        a == b ? "true" : "false");
}
void adv()
{
    //funcptr();
    // vargs();
    // errmsg();
    // bitfields();
    // volat();
    // locales();
    wchars();
    // scansets();
}
void scansets()
{
    setlocale(LC_ALL, "C");

    char a[100];
    char b[100];
    int c;

    printf("Enter input in the format 'string1#string2#integer': ");
    scanf("%[^#A-Z]#%[^#a-z]#%d", a, b, &c);

    printf("a: %s\n", a);
    printf("b: %s\n", b);
    printf("c: %d\n", c);
}