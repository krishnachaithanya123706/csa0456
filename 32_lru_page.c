/*
 * Q32: LRU (Least Recently Used) Page Replacement Algorithm
 */
#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES  50

int main() {
    int frames, n;
    int pages[MAX_PAGES];
    int frame[MAX_FRAMES], used[MAX_FRAMES];
    int page_faults = 0, timer = 0;

    printf("=== LRU Page Replacement ===\n");
    printf("Enter number of frames: "); scanf("%d", &frames);
    printf("Enter number of pages : "); scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    for (int i = 0; i < frames; i++) { frame[i] = -1; used[i] = 0; }

    printf("\n%-5s | %-20s | %s\n", "Page", "Frames", "Fault?");
    printf("------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        timer++;
        int found = -1;
        for (int j = 0; j < frames; j++)
            if (frame[j] == pages[i]) { found = j; break; }

        if (found != -1) {
            used[found] = timer;
        } else {
            /* Find empty or LRU slot */
            int replace = 0;
            for (int j = 1; j < frames; j++)
                if (frame[j] == -1 || used[j] < used[replace]) replace = j;
            frame[replace] = pages[i];
            used[replace]  = timer;
            page_faults++;
        }

        printf("%-5d | ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("| %s\n", (found == -1) ? "FAULT" : "");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Page Hit Rate    : %.2f%%\n", (float)(n - page_faults) / n * 100);
    return 0;
}
