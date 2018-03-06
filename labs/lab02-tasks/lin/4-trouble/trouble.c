/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #4, Linux
 *
 * Troubleshooting open and write functions
 */

#include "full_write.h"
#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int fd = open("tmp1.txt", O_CREAT | O_RDWR | O_CLOEXEC, 0644);
    DIE(fd < 0, "open failed");

    const char *msg = "Ana are mere!\n";
    ssize_t num_written = full_write(fd, msg, strlen(msg));
    DIE(num_written == -1, "write failed");

    int rc = close(fd);
    DIE(rc < 0, "close failed");

    return 0;
}

