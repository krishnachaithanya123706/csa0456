/*
 * Q28: Simulate UNIX 'grep' Command
 *      Searches for a pattern in a file and prints matching lines.
 *      Usage: ./grep_sim <pattern> <filename>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN 1024

/* Simple substring search (no regex) */
int contains(const char *line, const char *pattern) {
    return strstr(line, pattern) != NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pattern  = argv[1];
    const char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("fopen"); exit(EXIT_FAILURE); }

    printf("=== grep '%s' %s ===\n\n", pattern, filename);

    char line[LINE_MAX_LEN];
    int  line_no = 0, match_count = 0;

    while (fgets(line, LINE_MAX_LEN, fp)) {
        line_no++;
        if (contains(line, pattern)) {
            /* Remove trailing newline for display */
            line[strcspn(line, "\n")] = '\0';
            printf("%4d: %s\n", line_no, line);
            match_count++;
        }
    }

    fclose(fp);

    printf("\n%d match(es) found.\n", match_count);
    return (match_count > 0) ? 0 : 1;
}
