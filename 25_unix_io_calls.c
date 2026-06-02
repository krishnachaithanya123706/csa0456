/*
 * Q25: UNIX I/O System Calls: fcntl, lseek, stat, opendir, readdir
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define DEMO_FILE "demo_io.txt"

void demo_fcntl(int fd) {
    printf("\n--- fcntl() ---\n");
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) { perror("fcntl F_GETFL"); return; }
    printf("File flags: 0x%X  (%s)\n", flags,
           (flags & O_RDONLY) ? "O_RDONLY" :
           (flags & O_WRONLY) ? "O_WRONLY" : "O_RDWR");

    /* Set non-blocking flag */
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    printf("Non-blocking flag set.\n");
}

void demo_lseek(int fd) {
    printf("\n--- lseek() ---\n");
    off_t cur = lseek(fd, 0, SEEK_CUR);
    printf("Current offset : %ld\n", (long)cur);
    off_t end = lseek(fd, 0, SEEK_END);
    printf("End of file    : %ld bytes\n", (long)end);
    lseek(fd, 0, SEEK_SET);
    printf("Reset to start : offset = 0\n");
}

void demo_stat(const char *path) {
    printf("\n--- stat(\"%s\") ---\n", path);
    struct stat st;
    if (stat(path, &st) < 0) { perror("stat"); return; }
    printf("Size       : %ld bytes\n", (long)st.st_size);
    printf("Inode      : %lu\n", (unsigned long)st.st_ino);
    printf("Permissions: %o\n", st.st_mode & 0777);
    printf("Links      : %lu\n", (unsigned long)st.st_nlink);
    char time_buf[50];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S",
             localtime(&st.st_mtime));
    printf("Modified   : %s\n", time_buf);
}

void demo_opendir_readdir(const char *path) {
    printf("\n--- opendir/readdir(\"%s\") ---\n", path);
    DIR *dir = opendir(path);
    if (!dir) { perror("opendir"); return; }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);
}

int main() {
    printf("=== UNIX I/O System Calls Demo ===\n");

    /* Create and write a demo file */
    int fd = open(DEMO_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(EXIT_FAILURE); }
    write(fd, "Hello UNIX I/O Calls!\nLine 2 here.\n", 35);
    lseek(fd, 0, SEEK_SET);

    demo_fcntl(fd);
    demo_lseek(fd);
    close(fd);
    demo_stat(DEMO_FILE);
    demo_opendir_readdir(".");

    unlink(DEMO_FILE);
    printf("\nDemo complete.\n");
    return 0;
}
