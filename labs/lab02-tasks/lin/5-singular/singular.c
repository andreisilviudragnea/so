/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #5, Linux
 *
 * Locking a file
 */

#include "utils.h"
#include <errno.h>    /* errno */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>    /* flock */
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LOCK_FILE "/tmp/my_lock_file"

static int fdlock = -1;

static void do_stuff(void)
{
    sleep(10);
}

static void check_lock(void)
{
    /* fdlock = open(...) */
    fdlock = open(LOCK_FILE, O_CREAT | O_CLOEXEC, 0644);
    DIE(fdlock == -1, "open failed");

    errno = 0;
    int rc = flock(fdlock, LOCK_EX | LOCK_NB);
    DIE(rc == -1 && errno == EWOULDBLOCK, "flock would block");

    printf("\nGot Lock\n\n");
}

static void clean_up(void)
{
    int rc = flock(fdlock, LOCK_UN);
    DIE(rc == -1, "flock unlock failed");

    rc = close(fdlock);
    DIE(rc == -1, "close failed");

    rc = unlink(LOCK_FILE);
    DIE(rc == -1, "unlink failed");
}


int main(void)
{
    check_lock();

    do_stuff();

    clean_up();

    return 0;
}


