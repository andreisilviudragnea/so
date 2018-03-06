/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #2, Linux
 *
 * Relation between file pointers and file descriptors
 */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int fd1 = open("Makefile", O_RDWR | O_CLOEXEC);
    DIE(fd1 < 0, "open file.txt");

    off_t pos = lseek(fd1, 100, SEEK_SET);
    DIE(pos < 0, "lseek");

    int fd2 = dup(fd1);
    DIE(fd2 < 0, "dup");

    pos = lseek(fd2, 100, SEEK_CUR);

    /* printf("pos = %d\n", pos); */

    int rc = close(fd1);
    DIE(rc < 0, "fd1");

    return 0;
}
