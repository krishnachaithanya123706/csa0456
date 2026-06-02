/*
 * Q31: FIFO Page Replacement Algorithm
 */
#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES  50

int main() {
    int frames, n;
    int pages[MAX_PAGES];
    int frame[MAX_FRAMES];
    int page_faults = 0, ptr = 0;

    printf("=== FIFO Page Replacement ===\n");
    printf("Enter number of frames: "); scanf("%d", &frames);
    printf("Enter number of pages : "); scanf("%d", &n);
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("\n%-5s | %-20s | %s\n", "Page", "Frames", "Fault?");
    printf("------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++)
            if (frame[j] == pages[i]) { found = 1; break; }

        if (!found) {
            frame[ptr] = pages[i];
            ptr = (ptr + 1) % frames;
            page_faults++;
        }

        printf("%-5d | ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("| %s\n", found ? "" : "FAULT");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Page Hit Rate    : %.2f%%\n", (float)(n - page_faults) / n * 100);
    return 0;
}
