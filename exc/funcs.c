#include <stdio.h>
#include <stdlib.h>

#define NUM sizeof(wlist) / sizeof(char *)
int main(void){
    printf("Hello world!\n");
    /*float num = 1.8f/52.0f;
    float* r = &num;
    // char cc[] = 'char';
    printf("%p", (void *) r);
    float result = factorial(num);
    printf("The factorial of %f is: %f\n", num, result);
    int rr = fact(15);
    printf("  %d ", rr);*/
    // __mingw_vfprintf(NULL, c, NULL);
    // RunApplication();
    int x = 5;
    int y = 10;
    int z = 2;
    int pp = 3;
    int *p = &pp;

    struct {
        int x;
        int a;
    } s = {7, 4};

    union uis
    {
        char a;
        unsigned char b;
        long int c;
        double  d;
        short e;
        float f;
        char g;
        short h;
    } ui;
     char input[32];

    printf("Enter a value for 'a': ");
    gets(input); //, sizeof(input), stdin);
    ui.a = input;

    printf("Enter a value for 'b': ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%hhu", &ui.b);

    printf("Enter a value for 'g': ");
    fgets(input, sizeof(input), stdin);
    ui.g = input[0];
    // Print the values
    printf("Value of 'a': %c\n", ui.a);
printf("Value of 'b': %u\n", ui.b);
printf("Value of 'c': %ld\n", ui.c);
printf("Value of 'd': %lf\n", ui.d);
printf("Value of 'e': %hd\n", ui.e);
printf("Value of 'g': %c\n", ui.g);
// Treat the union as a block of memory
    unsigned char* mem = (unsigned char*)&ui;
    size_t size = sizeof(ui);

    // Print the values byte by byte
    for (size_t i = 0; i < size; i++) {
        printf("mem[%zu]: %u\n", i, mem[i]);
    }


    fputs(&s.x, stdout);
    putchar('\n');
    puts(&s.a);
    putchar('\n'); 

    int temp = (int)((float) sizeof(*p) - (intptr_t)(&pp) * (++y) - (--(s.x))) << s.a;
    x += (x != 0) ? temp : z;

    printf("x = %d\n", x);

    return 0;
}

int dumbcmp(const void *a, const void *b)
{
    return strcmp(*(char **)a, *(char **)b);
}
int compare(const void *arg1, const void *arg2)
{
    const int *a = arg1, *b = arg2;

    if (*a == *b)
        return 0;
    else if (*a < *b)
        return -1;
    else
        return 1;
}
#define NWIN 10
#define NNUM 25
void tmp(){
    for (int i = 1; i <= 100; i++)
    {
        char fb[32]; // Create a character array to store the FizzBuzz result
        fb[0] = 0;   // Initialize the array with a null character to indicate an empty string

        // Check if i is divisible by 3 and append "Fizz" to fb if true
        if (i % 3 == 0)
            strcat(fb, "Fizz");

        // Check if i is divisible by 5 and append "Buzz" to fb if true
        if (i % 5 == 0)
            strcat(fb, "Buzz");

        // If fb is still an empty string, convert i to a string and store it in fb
        if (!fb[0])
            sprintf(fb, "%d", i);

        // Print the FizzBuzz result
        puts(fb);
    }
    const char *s = "2147483647";
    int n = atoi(s);
    if (n + 1 < n)
    {
        puts("Overflow!");
    }
    else
    {
        puts("No overflow");
    }
    printf("%d\n", n + 1);
    for (int i = -1; i >= -260; i--)
    {
        printf("Character code for %d: %c\n", i, (char)i);
    }

    int array[6] = {7, 2, 6, 1, 2, 5};

    qsort(array, 6, sizeof array[0], compare);

    for (int i = 0; i < 6; ++i)
    {
        printf("%d\n", array[i]);
    }

    char *wlist[] = {
        "aids", "crud", "evil", "gall", "idiot", "kick",
        "moon", "oval", "quod", "sulk", "under", "west",
        "year"};

    char *word = "evil";
    int found;

    found = (bsearch(&word, wlist, NUM, sizeof(char *), dumbcmp) != NULL);
    printf("%d\n", found);

    int spaces_count = 0;
    int current_character;
    while ((current_character = getchar()) != EOF)
    {
        if (isspace(current_character))
            spaces_count++;
        else
            spaces_count = 0;

        if (spaces_count > 0)
            putchar(spaces_count);
    }

    
    size_t sum1, sum2;
    size_t copies[NWIN] = {0};
    size_t index;
    int winning[NWIN];
    size_t score;
    size_t n;
    size_t i, j;
    int number;

    index = 0;
    sum1 = sum2 = 0;
    while (scanf("Card %*d: ") != EOF)
    {
        for (i = 0; i < NWIN; i++)
            scanf("%d ", &winning[i]);
        scanf("| ");
        score = 0;
        for (i = 0; i < NNUM; i++)
        {
            scanf("%d ", &number);
            for (j = 0; j < NWIN; j++)
                if (number == winning[j])
                {
                    score++;
                    break;
                }
        }
        if (score > 0)
            sum1 += 1 << (score - 1);
        n = copies[index] + 1;
        sum2 += n;
        for (i = 1; i <= score; i++)
            copies[(index + i) % NWIN] += n;
        copies[index] = 0;
        index = (index + 1) % NWIN;

        int *p = malloc(sizeof(int));
    free(p);
    int *q = malloc(sizeof(int));
    *q = 10;
    *p = 20;
    printf("%d\n", *p);
    char cd[20];
    int ci;
    scanf("Card %*d: %s", &ci, &cd);
    int gc;
    while(1){
        
    printf("--------\aB\te\ve\np\r!\x1f\n");
    gc = getchar();

    int ef = gc != EOF;
    
    printf("%d %d %zu %s\n", gc, ef, ci, cd);
    }
    system((const char *)"pause");
    }
}