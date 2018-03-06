/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #3, Linux
 *
 * cat/cp applications
 */

#include "full_write.h"
#include "utils.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 32

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        printf("Usage:\n\t%s source_file [destination_file]\n", argv[0]);
        return 0;
    }

    int fd_src = open(argv[1], O_RDONLY | O_CLOEXEC);
    DIE(fd_src == -1, "opening input file failed");


    if (argc == 3) {
        int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
                          0644);
        DIE(fd_dst == -1, "opening output file failed");

        int rc = dup2(fd_dst, STDOUT_FILENO);
        DIE(rc == -1, "dup2 failed");

        rc = close(fd_dst);
        DIE(rc == -1, "close fd_dst failed");
    }

    while (true) {
        char buffer[BUFSIZE];
        ssize_t num_read = read(fd_src, buffer, BUFSIZE);
        DIE(num_read == -1, "read failed");
        if (num_read == 0) {
            break;
        }
        ssize_t num_written = full_write(STDOUT_FILENO, buffer,
                                         (size_t) num_read);
        DIE(num_written == -1, "write failed");
    }

    int rc = close(fd_src);
    DIE(rc == -1, "close failed");

    return 0;
}
