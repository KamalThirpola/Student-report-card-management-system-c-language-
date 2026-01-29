#include <stdio.h>
#include <stdlib.h>

struct student {
    int roll;
    char name[50];
    int marks[5];
    int total;
    float percentage;
    char grade;
};

void calculate(struct student *s) {
    s->total = 0;
    for (int i = 0; i < 5; i++)
        s->total += s->marks[i];

    s->percentage = s->total / 5.0;

    if (s->percentage >= 90) s->grade = 'A';
    else if (s->percentage >= 75) s->grade = 'B';
    else if (s->percentage >= 60) s->grade = 'C';
    else if (s->percentage >= 40) s->grade = 'D';
    else s->grade = 'F';
}

void addStudent() {
    FILE *fp;
    struct student s;

    fp = fopen("data/student.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    for (int i = 0; i < 5; i++) {
        printf("Enter marks of subject %d: ", i + 1);
        scanf("%d", &s.marks[i]);
    }

    calculate(&s);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent record added successfully!");
}

void displayStudents() {
    FILE *fp;
    struct student s;

    fp = fopen("data/student.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!");
        return;
    }

    printf("\nRoll\tName\t\tTotal\tPercent\tGrade");
    printf("\n------------------------------------------------");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\n%d\t%s\t\t%d\t%.2f\t%c",
               s.roll, s.name, s.total, s.percentage, s.grade);
    }
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n\nSTUDENT REPORT CARD SYSTEM");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: exit(0);
            default: printf("\nInvalid choice!");
        }
    }
}
