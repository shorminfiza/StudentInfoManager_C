#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STUDENTS 100

typedef struct {
    uint32_t id;
    char *name;
    float cgpa;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    students[studentCount].name = (char *)malloc(100 * sizeof(char));  // Allocate memory

    printf("Enter ID: ");
    scanf("%u", &students[studentCount].id);

    printf("Enter Name: ");
    getchar(); // To consume leftover newline
    fgets(students[studentCount].name, 100, stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0'; // remove newline

    printf("Enter CGPA: ");
    scanf("%f", &students[studentCount].cgpa);

    studentCount++;
    printf("Student added successfully!\n");
}

void viewStudents() {
    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\n---- All Students ----\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %u | Name: %s | CGPA: %.2f\n", students[i].id, students[i].name, students[i].cgpa);
    }
    printf("----------------------\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Student\n2. View Students\n3. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                // Free all allocated memory before exiting
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].name);
                }
                printf("Goodbye!\n_Boss\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}