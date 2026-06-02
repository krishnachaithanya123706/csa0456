/*
 * Q15: Two Level Directory Structure
 *      Each user has their own sub-directory of files.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS  5
#define MAX_FILES  10
#define NAME_LEN   30

typedef struct {
    char name[NAME_LEN];
    int  size;
} File;

typedef struct {
    char username[NAME_LEN];
    File files[MAX_FILES];
    int  file_count;
} UserDir;

UserDir users[MAX_USERS];
int user_count = 0;

UserDir *find_user(const char *uname) {
    for (int i = 0; i < user_count; i++)
        if (strcmp(users[i].username, uname) == 0) return &users[i];
    return NULL;
}

UserDir *create_user(const char *uname) {
    if (user_count >= MAX_USERS) { printf("Max users reached.\n"); return NULL; }
    UserDir *u = &users[user_count++];
    strncpy(u->username, uname, NAME_LEN - 1);
    u->file_count = 0;
    printf("User '%s' directory created.\n", uname);
    return u;
}

void create_file(const char *uname, const char *fname, int size) {
    UserDir *u = find_user(uname);
    if (!u) u = create_user(uname);
    if (!u) return;
    for (int i = 0; i < u->file_count; i++) {
        if (strcmp(u->files[i].name, fname) == 0) {
            printf("File '%s' already exists for user '%s'.\n", fname, uname);
            return;
        }
    }
    if (u->file_count >= MAX_FILES) { printf("User directory full.\n"); return; }
    strncpy(u->files[u->file_count].name, fname, NAME_LEN - 1);
    u->files[u->file_count].size = size;
    u->file_count++;
    printf("File '%s' created for user '%s'.\n", fname, uname);
}

void list_all() {
    for (int i = 0; i < user_count; i++) {
        printf("\nUser: %s\n", users[i].username);
        printf("  %-20s %-10s\n", "Filename", "Size(KB)");
        printf("  --------------------------------\n");
        for (int j = 0; j < users[i].file_count; j++) {
            printf("  %-20s %-10d\n", users[i].files[j].name, users[i].files[j].size);
        }
    }
}

void search_file(const char *uname, const char *fname) {
    UserDir *u = find_user(uname);
    if (!u) { printf("User '%s' not found.\n", uname); return; }
    for (int i = 0; i < u->file_count; i++) {
        if (strcmp(u->files[i].name, fname) == 0) {
            printf("Found: %s/%s  (%d KB)\n", uname, fname, u->files[i].size);
            return;
        }
    }
    printf("File '%s' not found for user '%s'.\n", fname, uname);
}

int main() {
    int ch; char uname[NAME_LEN], fname[NAME_LEN]; int sz;
    printf("=== Two Level Directory Structure ===\n");
    do {
        printf("\n1.Create File  2.List All  3.Search  4.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Username: "); scanf("%s", uname);
                printf("Filename: "); scanf("%s", fname);
                printf("Size(KB): "); scanf("%d", &sz);
                create_file(uname, fname, sz);
                break;
            case 2: list_all(); break;
            case 3:
                printf("Username: "); scanf("%s", uname);
                printf("Filename: "); scanf("%s", fname);
                search_file(uname, fname);
                break;
            case 4: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 4);
    return 0;
}
