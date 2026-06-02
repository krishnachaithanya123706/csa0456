/*
 * Q27: Simulate UNIX 'ls' Command
 *      Displays directory entries with type and size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void list_dir(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) { perror("opendir"); exit(EXIT_FAILURE); }

    struct dirent *entry;
    struct stat st;
    char full_path[512];
    char time_buf[30];

    printf("%-10s %-8s %-20s %s\n", "Perms", "Size", "Modified", "Name");
    printf("-----------------------------------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue; /* skip hidden */

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &st) < 0) continue;

        char type = S_ISDIR(st.st_mode) ? 'd' : '-';
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M",
                 localtime(&st.st_mtime));

        printf("%c%c%c%c%c%c%c%c%c%c %-8ld %-20s %s\n",
               type,
               (st.st_mode & S_IRUSR) ? 'r' : '-',
               (st.st_mode & S_IWUSR) ? 'w' : '-',
               (st.st_mode & S_IXUSR) ? 'x' : '-',
               (st.st_mode & S_IRGRP) ? 'r' : '-',
               (st.st_mode & S_IWGRP) ? 'w' : '-',
               (st.st_mode & S_IXGRP) ? 'x' : '-',
               (st.st_mode & S_IROTH) ? 'r' : '-',
               (st.st_mode & S_IWOTH) ? 'w' : '-',
               (st.st_mode & S_IXOTH) ? 'x' : '-',
               (long)st.st_size,
               time_buf,
               entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    printf("=== Simulated 'ls -l' for: %s ===\n\n", path);
    list_dir(path);
    return 0;
}
