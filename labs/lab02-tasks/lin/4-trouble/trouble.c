/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #4, Linux
 *
 * Troubleshooting open and write functions
 */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    /* opening files */
    int fd = open("tmp1.txt", O_CREAT | O_RDWR | O_CLOEXEC, 0644);
    DIE(fd < 0, "open failed");

    const char *msg = "Ana are mere!\n";
    ssize_t rc = write(fd, msg, strlen(msg));
    DIE(rc < 0, "write failed");

    rc = close(fd);
    DIE(rc < 0, "close failed");

    return 0;
}

