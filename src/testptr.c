#include <stdio.h>

struct Person {
    char name[64];
    int age;
};

int ptrp(int argc, char *argv[]) {
    int avdur = 0xABCD0;
    struct Person people[100];
    struct Person *p_Person = &people[0];
    int j = 0xABCD1;
    printf("%x %c", avdur,j);
    for (int i = 0; i < 100; i++) {
        p_Person->age = 0;
        p_Person->name[0] = 0;
        p_Person+=4;
        printf("%d %p %d\n", i, p_Person, people[i].age);
    }
    printf("%p %d", p_Person, people[0].age);
    
    return 0;
}