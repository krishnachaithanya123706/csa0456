/*
 * Q35: Indexed File Allocation Simulation
 *      An index block holds pointers to all data blocks of a file.
 */
#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS  20
#define MAX_FILES    5
#define MAX_INDEX    8
#define NAME_LEN    20

int disk[MAX_BLOCKS];   /* 0 = free, 1 = used */

typedef struct {
    char name[NAME_LEN];
    int  index_block;
    int  data_blocks[MAX_INDEX];
    int  num_blocks;
} IndexedFile;

IndexedFile files[MAX_FILES];
int file_count = 0;

void init() { memset(disk, 0, sizeof(disk)); }

int alloc_block() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        if (!disk[i]) { disk[i] = 1; return i; }
    return -1;
}

void create_file(const char *name, int n) {
    if (file_count >= MAX_FILES) { printf("Max files reached.\n"); return; }
    IndexedFile *f = &files[file_count];
    strncpy(f->name, name, NAME_LEN - 1);
    f->num_blocks = n;

    f->index_block = alloc_block();
    if (f->index_block == -1) { printf("No block for index.\n"); return; }

    printf("Allocating '%s': index=%d, data=", name, f->index_block);
    for (int i = 0; i < n; i++) {
        f->data_blocks[i] = alloc_block();
        if (f->data_blocks[i] == -1) { printf("\nOut of disk space.\n"); return; }
        printf("%d ", f->data_blocks[i]);
    }
    printf("\n");
    file_count++;
}

void display() {
    printf("\nDisk Map:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) printf("[%2d]:%d ", i, disk[i]);
    printf("\n\nIndex Table:\n");
    printf("%-12s %-8s %s\n", "File", "Index", "Data Blocks");
    printf("--------------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-12s %-8d ", files[i].name, files[i].index_block);
        for (int j = 0; j < files[i].num_blocks; j++)
            printf("%d ", files[i].data_blocks[j]);
        printf("\n");
    }
}

int main() {
    int ch, n; char name[NAME_LEN];
    init();
    printf("=== Indexed File Allocation ===\n");
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
