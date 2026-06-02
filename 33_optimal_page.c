/*
 * Q33: Optimal Page Replacement Algorithm
 *      Replaces the page that will not be used for the longest time in future.
 */
#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES  50

int main() {
    int frames, n;
    int pages[MAX_PAGES];
    int frame[MAX_FRAMES];
    int page_faults = 0;

    printf("=== Optimal Page Replacement ===\n");
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
            /* Check if there's empty slot */
            int empty = -1;
            for (int j = 0; j < frames; j++)
                if (frame[j] == -1) { empty = j; break; }

            if (empty != -1) {
                frame[empty] = pages[i];
            } else {
                /* Find page used farthest in future */
                int farthest = -1, replace = 0;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++)
                        if (frame[j] == pages[k]) break;
                    if (k == n) { replace = j; break; }
                    if (k > farthest) { farthest = k; replace = j; }
                }
                frame[replace] = pages[i];
            }
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
