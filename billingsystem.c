#include <stdio.h>

#include <stdlib.h>

#include <string.h>

 

struct Student {

    char name[100];

    int roll;

    int class;

    float fees_total;

    float fees_paid;

    struct Student* next;

};

 

typedef struct Student Student;

 

Student* createStudent(char name[], int roll, int class, float fees_total) {

    Student* student = (Student*)malloc(sizeof(Student));

    strcpy(student->name, name);

    student->roll = roll;

    student->class = class;

    student->fees_total = fees_total;

    student->fees_paid = 0.0;

    student->next = NULL;

    return student;

}

 

void addStudent(Student** head, Student* newStudent) {

    if (*head == NULL) {

        *head = newStudent;

    } else {

        Student* current = *head;

        while (current->next != NULL) {

            current = current->next;

        }

        current->next = newStudent;

    }

}

 

void deleteStudent(Student** head, int roll) {

    if (*head == NULL) {

        return;

    }

    if ((*head)->roll == roll) {

        Student* temp = *head;

        *head = (*head)->next;

        free(temp);

        return;

    }

    Student* current = *head;

    while (current->next != NULL && current->next->roll != roll) {

        current = current->next;

    }

    if (current->next == NULL) {
printf("--------------------------------------------------------------------------\n");
        printf("Student with roll number %d not found.\n", roll);

        return;

    }

    Student* temp = current->next;

    current->next = current->next->next;

    free(temp);

}

 

Student* searchStudentByName(Student* head, char name[]) {

    Student* current = head;

    while (current != NULL) {

        if (strcmp(current->name, name) == 0) {

            return current;

        }

        current = current->next;

    }

    return NULL;

}

 

void displayStudents(Student* head) {
    printf("\n********************************************************\n");

    printf("%-20s %-10s %-10s %-15s %-15s %-15s\n", "Name", "Roll", "Class", "Total Fees", "Fees Paid", "Pending Fees");

    printf("--------------------------------------------------------------------------\n");

    Student* current = head;

    while (current != NULL) {

        float pendingFees = current->fees_total - current->fees_paid;

        printf("%-20s %-10d %-10d %-15.2f %-15.2f %-15.2f\n",

               current->name, current->roll, current->class, current->fees_total, current->fees_paid, pendingFees);

        current = current->next;

    }

}

 

void updateFeesPayment(Student* student, float amount) {

    student->fees_paid += amount;

}

 

Student* findStudentByRoll(Student* head, int roll) {

    Student* current = head;

    while (current != NULL) {

        if (current->roll == roll) {

            return current;

        }

        current = current->next;

    }

    return NULL;

}

 

void saveStudentsToFile(Student* head, const char* filename) {

    FILE* file = fopen(filename, "w");

    if (file == NULL) {

        perror("Error opening file for writing");

        return;

    }

    Student* current = head;

    while (current != NULL) {

        fprintf(file, "%s %d %d %.2f %.2f\n",

                current->name, current->roll, current->class, current->fees_total, current->fees_paid);

        current = current->next;

    }

    fclose(file);

    printf("Student data saved to %s\n", filename);

}

 

Student* loadStudentsFromFile(const char* filename) {

    FILE* file = fopen(filename, "r");

    if (file == NULL) {

        perror("Error opening file for reading");

        return NULL;

    }

    Student* head = NULL;

    char name[100];

    int roll, class;

    float fees_total, fees_paid;

    while (fscanf(file, "%s %d %d %f %f", name, &roll, &class, &fees_total, &fees_paid) != EOF) {

        Student* student = createStudent(name, roll, class, fees_total);

        student->fees_paid = fees_paid;

        addStudent(&head, student);

    }

    fclose(file);

    printf("Student data loaded from %s\n", filename);

    return head;

}

 

int main() {

    Student* studentList = NULL;

 

    int choice;

    while (1) {
        printf("\n********************************************************\n");
       
        printf("\nSchool Billing System                                   *\n");
       
         printf("\n********************************************************\n");

        printf("1. Add Student\n");

        printf("2. Display Students\n");

        printf("3. Update Fees Payment\n");

        printf("4. Save Students to File\n");

        printf("5. Load Students from File\n");

        printf("6. Delete Student\n");

        printf("7. Search by Name\n");

        printf("8. Exit\n");

        printf("Enter your choice: ");
         printf("\n********************************************************\n");
        scanf("%d", &choice);

 

        switch (choice) {

            case 1: {

                char name[100];

                int roll, class;

                float fees_total;

                printf("Enter student name: ");
                 
                 printf("\n----------------------------------------------------\n");
                 
                scanf("%s", name);

                printf("\n----------------------------------------------------\n");
                printf("Enter roll number: ");

                scanf("%d", &roll);
               
                printf("\n----------------------------------------------------\n");
                printf("Enter class: ");

                scanf("%d", &class);

                printf("\n----------------------------------------------------\n");
                printf("Enter total fees: ");

                scanf("%f", &fees_total);

                addStudent(&studentList, createStudent(name, roll, class, fees_total));
                printf("\n********************************************************\n");

                printf("Student added successfully.\n");

                break;

            }

            case 2: {

                displayStudents(studentList);

                break;

            }

            case 3: {

                int roll;

                float amount;
        printf("\n********************************************************\n");

                printf("Enter roll number: ");

                scanf("%d", &roll);

                Student* student = findStudentByRoll(studentList, roll);

                if (student != NULL) {
 printf("--------------------------------------------------------------------------\n");

                    printf("Enter payment amount: ");

                    scanf("%f", &amount);

                    if (amount <= 0) {
    printf("--------------------------------------------------------------------------\n");

                        printf("Payment amount should be positive.\n");

                        break;

                    }

                    updateFeesPayment(student, amount);
    printf("--------------------------------------------------------------------------\n");

                    printf("Fees payment updated successfully.\n");

                } else {
printf("--------------------------------------------------------------------------\n");
                    printf("Student with roll number %d not found.\n", roll);

                }

                break;

            }

            case 4: {

                saveStudentsToFile(studentList, "student_data.txt");

                break;

            }

            case 5: {

                studentList = loadStudentsFromFile("student_data.txt");

                break;

            }

            case 6: {

                int roll;
 printf("\n********************************************************\n");
                printf("Enter roll number to delete: ");

                scanf("%d", &roll);

                deleteStudent(&studentList, roll);
 printf("\n********************************************************\n");
                printf("Student with roll number %d deleted (if found).\n", roll);

                break;

            }

            case 7: {

                char name[100];
 printf("\n********************************************************\n");
                printf("Enter student name to search: ");

                scanf("%s", name);

                Student* student = searchStudentByName(studentList, name);

                if (student != NULL) {
printf("--------------------------------------------------------------------------\n");
                    printf("Student found:\n");

                    printf("Name: %s\nRoll: %d\nClass: %d\nTotal Fees: %.2f\nFees Paid: %.2f\nPending Fees: %.2f\n",

                           student->name, student->roll, student->class, student->fees_total, student->fees_paid,

                           student->fees_total - student->fees_paid);

                } else {

                    printf("Student with name '%s' not found.\n", name);

                }

                break;

            }

            case 8: {

                Student* current = studentList;

                while (current != NULL) {

                    Student* temp = current;

                    current = current->next;

                    free(temp);

                }
 printf("\n********************************************************\n");

                printf("Exiting program.\n");

                return 0;

            }

            default: {
 printf("\n********************************************************\n");

                printf("Invalid choice. Please enter a valid option.\n");

                break;

            }

        }

    }

 

    return 0;
}