#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Students {
    char name[36];
    char sex[2];
    int age;
} stud;

void student1();
void student2();
void student3();

int studs() {
    int cho;
    while (1) {
        printf("Add student info:\n");
        printf("1 - Student 1\n2 - Student 2\n3 - Student 3\n");
        scanf("%d", &cho);
        switch (cho) {
            case 1:
                student1();
                break;
            case 2:
                student2();
                break;
            case 3:
                student3();
                break;
            case 4:
                return 0;
            default:
                printf("Input error\n");
                break;
        }
    }
}

void student1() {
    stud student1;

    printf("Insert student info (age, sex, name): ");
    scanf("%d %[^\n]%*c", &student1.age, student1.sex);
    fgets(student1.name, sizeof(student1.name), stdin);

    printf("Age: %d\n", student1.age);
    printf("Sex: %s\n", student1.sex);
    printf("Name: %s", student1.name);
}

void student2() {
    stud student2;

    printf("Insert student info (age, sex, name): ");
    scanf("%d %[^\n]%*c", &student2.age, student2.sex);
    fgets(student2.name, sizeof(student2.name), stdin);

    printf("Age: %d\n", student2.age);
    printf("Sex: %s\n", student2.sex);
    printf("Name: %s", student2.name);
}

void student3() {
    stud student3;

    printf("Insert student info (age, sex, name): ");
    scanf("%d %[^\n]%*c", &student3.age, student3.sex);
    fgets(student3.name, sizeof(student3.name), stdin);

    printf("Age: %d\n", student3.age);
    printf("Sex: %s\n", student3.sex);
    printf("Name: %s", student3.name);
}