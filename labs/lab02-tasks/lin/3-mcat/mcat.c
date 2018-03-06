/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #3, Linux
 *
 * cat/cp applications
 */

#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 32

static void full_write(int fd, const void *buf, size_t count)
{
    while (true) {
        ssize_t num_written = write(fd, buf, count);
        DIE(num_written == -1, "write failed");
        count -= num_written;
        if (count == 0) {
            break;
        }
        buf += num_written;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        printf("Usage:\n\t%s source_file [destination_file]\n", argv[0]);
        return 0;
    }

    /* TODO 1 - open source file for reading */
    int fd_src = open(argv[1], O_RDONLY | O_CLOEXEC);
    DIE(fd_src == -1, "opening input file failed");


    if (argc == 3) {
        /* TODO 2 - redirect stdout to destination file */
        int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
                          0644);
        DIE(fd_dst == -1, "opening output file failed");

        int rc = dup2(fd_dst, STDOUT_FILENO);
        DIE(rc == -1, "dup2 failed");

        rc = close(fd_dst);
        DIE(rc == -1, "close fd_dst failed");
    }

    /* TODO 1 - read from file and print to stdout
     * use _only_ read and write functions
     */
    while (true) {
        char buffer[BUFSIZE];
        ssize_t num_read = read(fd_src, buffer, BUFSIZE);
        DIE(num_read == -1, "read failed");
        if (num_read == 0) {
            break;
        }
        full_write(STDOUT_FILENO, buffer, (size_t) num_read);
    }

    /* TODO 1 - close file */
    int rc = close(fd_src);
    DIE(rc == -1, "close failed");

    return 0;
}
