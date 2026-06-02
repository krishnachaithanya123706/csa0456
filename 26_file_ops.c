/*
 * Q26: File Management Operations
 *      Menu-driven: create, read, write, append, delete, rename, copy
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 512

void create_file(const char *name) {
    FILE *fp = fopen(name, "w");
    if (!fp) { perror("create"); return; }
    printf("Enter content (end with empty line):\n");
    char line[BUF];
    while (fgets(line, BUF, stdin)) {
        if (strcmp(line, "\n") == 0) break;
        fputs(line, fp);
    }
    fclose(fp);
    printf("File '%s' created.\n", name);
}

void read_file(const char *name) {
    FILE *fp = fopen(name, "r");
    if (!fp) { perror("read"); return; }
    printf("--- Contents of '%s' ---\n", name);
    char ch; while ((ch = fgetc(fp)) != EOF) putchar(ch);
    fclose(fp);
}

void append_file(const char *name) {
    FILE *fp = fopen(name, "a");
    if (!fp) { perror("append"); return; }
    printf("Enter text to append:\n");
    char line[BUF]; fgets(line, BUF, stdin); fgets(line, BUF, stdin);
    fputs(line, fp);
    fclose(fp);
    printf("Content appended.\n");
}

void delete_file(const char *name) {
    if (remove(name) == 0) printf("File '%s' deleted.\n", name);
    else perror("delete");
}

void rename_file(const char *old, const char *nw) {
    if (rename(old, nw) == 0) printf("Renamed '%s' -> '%s'.\n", old, nw);
    else perror("rename");
}

void copy_file(const char *src, const char *dst) {
    FILE *s = fopen(src, "r"), *d = fopen(dst, "w");
    if (!s || !d) { perror("copy"); return; }
    char ch; while ((ch = fgetc(s)) != EOF) fputc(ch, d);
    fclose(s); fclose(d);
    printf("Copied '%s' -> '%s'.\n", src, dst);
}

int main() {
    int ch; char f1[100], f2[100];
    printf("=== File Management Operations ===\n");
    do {
        printf("\n1.Create  2.Read  3.Append  4.Delete  5.Rename  6.Copy  7.Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: printf("Filename: "); scanf("%s", f1); create_file(f1); break;
            case 2: printf("Filename: "); scanf("%s", f1); read_file(f1); break;
            case 3: printf("Filename: "); scanf("%s", f1); append_file(f1); break;
            case 4: printf("Filename: "); scanf("%s", f1); delete_file(f1); break;
            case 5:
                printf("Old name: "); scanf("%s", f1);
                printf("New name: "); scanf("%s", f2);
                rename_file(f1, f2); break;
            case 6:
                printf("Source: "); scanf("%s", f1);
                printf("Dest  : "); scanf("%s", f2);
                copy_file(f1, f2); break;
            case 7: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while (ch != 7);
    return 0;
}
