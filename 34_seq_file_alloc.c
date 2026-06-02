/*
 * Q34: Sequential File Allocation Simulation
 *      Files are stored in contiguous disk blocks.
 */
#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 20
#define MAX_FILES  10
#define NAME_LEN   20

typedef struct {
    char name[NAME_LEN];
    int  start;
    int  length;
} FileEntry;

int disk[MAX_BLOCKS];        /* 0 = free, 1 = occupied */
FileEntry files[MAX_FILES];
int file_count = 0;

void init_disk() { memset(disk, 0, sizeof(disk)); }

int allocate(const char *name, int len) {
    /* Find contiguous free blocks */
    int start = -1, cnt = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!disk[i]) {
            if (start == -1) start = i;
            cnt++;
            if (cnt == len) {
                for (int j = start; j < start + len; j++) disk[j] = 1;
                strncpy(files[file_count].name, name, NAME_LEN - 1);
                files[file_count].start  = start;
                files[file_count].length = len;
                file_count++;
                printf("Allocated '%s': blocks %d - %d\n", name, start, start + len - 1);
                return 1;
            }
        } else { start = -1; cnt = 0; }
    }
    printf("Allocation failed for '%s' (need %d contiguous blocks)\n", name, len);
    return 0;
}

void display() {
    printf("\nDisk Block Map (0=free, 1=used):\n");
    for (int i = 0; i < MAX_BLOCKS; i++) printf("[%2d]:%d ", i, disk[i]);
    printf("\n\nFile Table:\n");
    printf("%-12s %-8s %-8s\n", "File", "Start", "Length");
    printf("------------------------------\n");
    for (int i = 0; i < file_count; i++)
        printf("%-12s %-8d %-8d\n", files[i].name, files[i].start, files[i].length);
}

int main() {
    int ch, len; char name[NAME_LEN];
    init_disk();
    printf("=== Sequential File Allocation ===\n");
    do {
        printf("\n1.Allocate  2.Display  3.Exit\nChoice: "); scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("File name : "); scanf("%s", name);
                printf("Blocks needed: "); scanf("%d", &len);
                allocate(name, len); break;
            case 2: display(); break;
            case 3: printf("Exiting.\n"); break;
            default: printf("Invalid.\n");
        }
    } while (ch != 3);
    return 0;
}
