/*
 * Q24: UNIX System Calls for File Management
 *      Demonstrates: creat, open, read, write, close, unlink, rename
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE1 "demo_file.txt"
#define FILE2 "demo_renamed.txt"

int main() {
    int fd;
    char buf[100];
    ssize_t n;

    printf("=== UNIX File Management System Calls ===\n\n");

    /* 1. creat() - Create a new file */
    fd = creat(FILE1, 0644);
    if (fd < 0) { perror("creat"); exit(EXIT_FAILURE); }
    printf("1. creat(\"%s\") -> fd=%d\n", FILE1, fd);
    close(fd);

    /* 2. open() + write() */
    fd = open(FILE1, O_WRONLY);
    if (fd < 0) { perror("open for write"); exit(EXIT_FAILURE); }
    const char *msg = "Hello, UNIX File System Calls!\n";
    write(fd, msg, strlen(msg));
    printf("2. open+write: wrote \"%s\"", msg);
    close(fd);

    /* 3. open() + read() */
    fd = open(FILE1, O_RDONLY);
    if (fd < 0) { perror("open for read"); exit(EXIT_FAILURE); }
    n = read(fd, buf, sizeof(buf) - 1);
    buf[n] = '\0';
    printf("3. open+read : \"%s\"", buf);
    close(fd);

    /* 4. rename() */
    if (rename(FILE1, FILE2) == 0)
        printf("4. rename(\"%s\", \"%s\") -> success\n", FILE1, FILE2);
    else
        perror("rename");

    /* 5. unlink() - delete */
    if (unlink(FILE2) == 0)
        printf("5. unlink(\"%s\") -> deleted\n", FILE2);
    else
        perror("unlink");

    printf("\nAll file management system calls demonstrated.\n");
    return 0;
}
