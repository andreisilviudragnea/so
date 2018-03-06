/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #1, Linux
 *
 * Redirection example with "dup" and "dup2"
 * and use of "lsof"
 */

#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void wait_for_input(const char *msg)
{
    char buf[32];

    printf(" * %s\n", msg);
    printf(" -- Press ENTER to continue ...");
    fflush(stdout);
    fgets(buf, 32, stdin);
}


int main(void)
{
    wait_for_input("beginning");

    /* opening files */
    int fd1 = open("tmp1.txt", O_CREAT | O_RDWR | O_CLOEXEC, 0644);
    DIE(fd1 < 0, "open tmp1.txt");
    wait_for_input("created tmp1.txt");

    int fd2 = open("Makefile", O_RDONLY | O_CLOEXEC);
    DIE(fd2 < 0, "open Makefile");
    wait_for_input("opened Makefile");

    /* redirect sterr to fd1 */
    int rc = close(STDERR_FILENO);
    DIE(rc < 0, "close stderr");
    wait_for_input("closed stderr");

    rc = dup(fd1);
    DIE(rc < 0, "dup fd1");
    wait_for_input("dup - redirected stderr to fd1");

    rc = close(fd1);
    DIE(rc < 0, "close fd1");
    wait_for_input("closed fd1");

    /* redirect stderr to fd2 */
    rc = dup2(fd2, STDERR_FILENO);
    DIE(rc < 0, "dup2 fd2");
    wait_for_input("dup2 - redirected stderr to fd2");

    rc = close(fd2);
    DIE(rc < 0, "close fd2");
    wait_for_input("closed fd2");

    return 0;
}
