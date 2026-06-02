/*
 * Q14: Single Level Directory Structure
 *      Simulates a flat directory with create, delete, search, list.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 20
#define NAME_LEN  30

typedef struct {
    char name[NAME_LEN];
    int  size;
    char type[10];
} File;

File dir[MAX_FILES];
int count = 0;

void create_file(const char *name, int size, const char *type) {
    for (int i = 0; i < count; i++) {
        if (strcmp(dir[i].name, name) == 0) {
            printf("Error: File '%s' already exists.\n", name);
            return;
        }
    }
    if (count >= MAX_FILES) { printf("Directory full!\n"); return; }
    strncpy(dir[count].name, name, NAME_LEN - 1);
    dir[count].size = size;
    strncpy(dir[count].type, type, 9);
    count++;
    printf("File '%s' created.\n", name);
}

void delete_file(const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(dir[i].name, name) == 0) {
            dir[i] = dir[--count];
            printf("File '%s' deleted.\n", name);
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

void search_file(const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(dir[i].name, name) == 0) {
            printf("Found: %s | Size: %d KB | Type: %s\n",
                   dir[i].name, dir[i].size, dir[i].type);
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

void list_files() {
    if (count == 0) { printf("Directory is empty.\n"); return; }
    printf("\n%-20s %-10s %-10s\n", "Filename", "Size(KB)", "Type");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d %-10s\n", dir[i].name, dir[i].size, dir[i].type);
    }
}

int main() {
    int ch; char name[NAME_LEN]; int sz; char type[10];
    printf("=== Single Level Directory ===\n");
    do {
        printf("\n1.Create  2.Delete  3.Search  4.List  5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Filename: "); scanf("%s", name);
                printf("Size(KB): "); scanf("%d", &sz);
                printf("Type    : "); scanf("%s", type);
                create_file(name, sz, type);
                break;
            case 2:
                printf("Filename: "); scanf("%s", name);
                delete_file(name);
                break;
            case 3:
                printf("Filename: "); scanf("%s", name);
                search_file(name);
                break;
            case 4: list_files(); break;
            case 5: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 5);
    return 0;
}
