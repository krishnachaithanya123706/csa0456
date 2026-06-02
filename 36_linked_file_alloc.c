/*
 * Q36: Linked File Allocation Simulation
 *      Each block contains a pointer to the next block (linked list on disk).
 */
#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 20
#define MAX_FILES   5
#define NAME_LEN   20

int disk[MAX_BLOCKS];    /* 0=free, 1=used */
int next[MAX_BLOCKS];    /* next[i] = next block of i, -1 = end */

typedef struct {
    char name[NAME_LEN];
    int  start;
    int  num_blocks;
} LinkedFile;

LinkedFile files[MAX_FILES];
int file_count = 0;

void init() {
    memset(disk, 0, sizeof(disk));
    for (int i = 0; i < MAX_BLOCKS; i++) next[i] = -1;
}

int alloc_block() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        if (!disk[i]) { disk[i] = 1; return i; }
    return -1;
}

void create_file(const char *name, int n) {
    if (file_count >= MAX_FILES) { printf("Max files reached.\n"); return; }
    LinkedFile *f = &files[file_count];
    strncpy(f->name, name, NAME_LEN - 1);
    f->num_blocks = n;

    int prev = -1, start = -1;
    printf("Allocating '%s': ", name);
    for (int i = 0; i < n; i++) {
        int blk = alloc_block();
        if (blk == -1) { printf("\nOut of disk space.\n"); return; }
        printf("%d ", blk);
        if (prev != -1) next[prev] = blk;
        else start = blk;
        prev = blk;
    }
    next[prev] = -1;
    f->start = start;
    printf("\n");
    file_count++;
}

void display() {
    printf("\nDisk Map:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) printf("[%2d]:%d ", i, disk[i]);
    printf("\n\nLinked File Table:\n");
    printf("%-12s %-8s %s\n", "File", "Start", "Block Chain");
    printf("--------------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-12s %-8d ", files[i].name, files[i].start);
        int blk = files[i].start;
        while (blk != -1) {
            printf("%d", blk);
            if (next[blk] != -1) printf(" -> ");
            blk = next[blk];
        }
        printf("\n");
    }
}

int main() {
    int ch, n; char name[NAME_LEN];
    init();
    printf("=== Linked File Allocation ===\n");
    do {
        printf("\n1.Create  2.Display  3.Exit\nChoice: "); scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("File name  : "); scanf("%s", name);
                printf("Num blocks : "); scanf("%d", &n);
                create_file(name, n); break;
            case 2: display(); break;
            case 3: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while (ch != 3);
    return 0;
}
