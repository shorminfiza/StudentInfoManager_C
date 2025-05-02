#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint32_t id;
    char *name;
    float cgpa;
} Student;

Student students[100];
int studentCount = 0;

void addStudent() {
    if (studentCount >= 100) {
        printf("Student limit reached!\n");
        return;
    }

    Student newStudent;
    printf("Enter ID: ");
    scanf("%u", &newStudent.id);

    getchar(); // Clear input buffer
    printf("Enter Name: ");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

    newStudent.name = malloc(strlen(buffer) + 1);
    if (newStudent.name == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newStudent.name, buffer);

    printf("Enter CGPA: ");
    scanf("%f", &newStudent.cgpa);

    students[studentCount++] = newStudent;
    printf("Student added successfully!\n");
}

void viewStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %u | Name: %s | CGPA: %.2f\n", students[i].id, students[i].name, students[i].cgpa);
    }
}

void searchStudent(uint32_t id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("ID: %u | Name: %s | CGPA: %.2f\n", students[i].id, students[i].name, students[i].cgpa);
            return;
        }
    }
    printf("Student with ID %u not found.\n", id);
}

void editStudent(uint32_t id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Editing Student with ID %u\n", id);

            printf("Enter new name: ");
            getchar(); // Clear buffer
            char buffer[100];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

            // Free old name and assign new
            free(students[i].name);
            students[i].name = malloc(strlen(buffer) + 1);
            if (students[i].name == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            strcpy(students[i].name, buffer);

            printf("Enter new CGPA: ");
            if (scanf("%f", &students[i].cgpa) != 1) {
                printf("Invalid CGPA input. Skipping update.\n");
                while (getchar() != '\n'); // clear input buffer
            } else {
                printf("Student updated successfully!\n");
            }
            return;
        }
    }
    printf("Student with ID %u not found.\n", id);
}


void deleteStudent(uint32_t id) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            free(students[i].name); // Free allocated memory
            // Shift all students left
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;

            // Clean the last element
            students[studentCount].id = 0;
            students[studentCount].name = NULL;
            students[studentCount].cgpa = 0.0;

            printf("Student with ID %u deleted successfully!\n", id);
            break;
        }
    }
    if (!found) {
        printf("Student with ID %u not found.\n", id);
    }
}

int main() {
    int choice;
    uint32_t id;

    while (1) {
        printf("\n--- Student Information Manager ---\n");
        printf("1. Add Student\n2. View Students\n3. Search Student\n4. Edit Student\n5. Delete Student\n6. Exit\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%u", &id);
                searchStudent(id);
                break;
            case 4:
                printf("Enter ID to edit: ");
                scanf("%u", &id);
                editStudent(id);
                break;
            case 5:
                printf("Enter ID to delete: ");
                scanf("%u", &id);
                deleteStudent(id);
                break;
            case 6:
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].name);
                }
                printf("Goodbye, Boss!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
