/*
 * Q16: Random Access File Processing of Employee Details
 *      Uses fseek() / fread() / fwrite() for record-level access.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "employees.dat"

typedef struct {
    int    emp_id;
    char   name[40];
    char   department[30];
    double salary;
} Employee;

void add_employee() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { perror("fopen"); return; }
    Employee e;
    printf("Employee ID  : "); scanf("%d", &e.emp_id);
    printf("Name         : "); scanf(" %[^\n]", e.name);
    printf("Department   : "); scanf(" %[^\n]", e.department);
    printf("Salary       : "); scanf("%lf", &e.salary);
    fwrite(&e, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Employee added.\n");
}

void display_all() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    Employee e;
    printf("\n%-6s %-20s %-15s %-10s\n", "ID", "Name", "Dept", "Salary");
    printf("-----------------------------------------------------\n");
    while (fread(&e, sizeof(Employee), 1, fp) == 1) {
        printf("%-6d %-20s %-15s %-10.2f\n",
               e.emp_id, e.name, e.department, e.salary);
    }
    fclose(fp);
}

void search_by_id(int id) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }
    Employee e;
    while (fread(&e, sizeof(Employee), 1, fp) == 1) {
        if (e.emp_id == id) {
            printf("ID: %d | Name: %s | Dept: %s | Salary: %.2f\n",
                   e.emp_id, e.name, e.department, e.salary);
            fclose(fp);
            return;
        }
    }
    printf("Employee ID %d not found.\n", id);
    fclose(fp);
}

void update_salary(int id, double new_salary) {
    FILE *fp = fopen(FILE_NAME, "r+b");
    if (!fp) { printf("No records found.\n"); return; }
    Employee e;
    long pos;
    while ((pos = ftell(fp)), fread(&e, sizeof(Employee), 1, fp) == 1) {
        if (e.emp_id == id) {
            e.salary = new_salary;
            fseek(fp, pos, SEEK_SET);
            fwrite(&e, sizeof(Employee), 1, fp);
            printf("Salary updated for employee %d.\n", id);
            fclose(fp);
            return;
        }
    }
    printf("Employee ID %d not found.\n", id);
    fclose(fp);
}

int main() {
    int ch, id; double sal;
    printf("=== Random Access Employee File ===\n");
    do {
        printf("\n1.Add  2.Display  3.Search  4.Update Salary  5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: add_employee(); break;
            case 2: display_all(); break;
            case 3: printf("Enter ID: "); scanf("%d", &id); search_by_id(id); break;
            case 4:
                printf("Enter ID: "); scanf("%d", &id);
                printf("New Salary: "); scanf("%lf", &sal);
                update_salary(id, sal);
                break;
            case 5: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 5);
    return 0;
}
