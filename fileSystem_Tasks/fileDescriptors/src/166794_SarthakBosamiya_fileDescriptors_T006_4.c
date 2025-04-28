// Question

/** REQUIRED HEADER FILES **/

#include<stdio.h>
#include"../include/head.h"

/*
 * Name of the function:
 * Author: Sarthak Bosamiya
 * Created: 21-04-2025
 * Modified: 21-04-2025
*/

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void task_4(void)
{
    char *c;
    int fd, sz, i;

    c = (char *) calloc(100, sizeof(char));
    if (!c) {
        perror("calloc");
        exit(1);
    }

    fd = open("in1", O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    sz = read(fd, c, 10);
    if (sz < 0) {
        perror("read");
        close(fd);
        free(c);
        exit(1);
    }

    printf("We have opened in1, and called read(%d, c, 10).\n", fd);
    printf("It returned that %d bytes were read.\n", sz);
    c[sz] = '\0';
    printf("Those bytes are as follows: %s\n", c);

    i = lseek(fd, 0, SEEK_CUR);
    printf("lseek(%d, 0, SEEK_CUR) returns that the current offset of the file is %d\n\n", fd, i);

    printf("Now, we seek to the beginning of the file and call read(%d, c, 10)\n", fd);
    lseek(fd, 0, SEEK_SET);
    sz = read(fd, c, 10);
    if (sz < 0) {
        perror("read");
        close(fd);
        free(c);
        exit(1);
    }
    c[sz] = '\0';
    printf("The read returns the following bytes: %s\n", c);

    printf("Now, we do lseek(%d, -6, SEEK_CUR). It returns %ld\n", fd, lseek(fd, -6, SEEK_CUR));
    printf("If we do read(%d, c, 10), we get the following bytes: ", fd);
    sz = read(fd, c, 10);
    if (sz < 0) {
        perror("read");
        close(fd);
        free(c);
        exit(1);
    }
    c[sz] = '\0';
    printf("%s\n", c);

    printf("Finally, we do lseek(%d, -1, SEEK_SET). This returns -1.\n", fd);
    printf("perror() tells us why: ");
    fflush(stdout);
    i = lseek(fd, -1, SEEK_SET);
    perror("lseek");

    close(fd);
    free(c);
}

