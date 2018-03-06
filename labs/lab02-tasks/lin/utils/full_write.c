//
// Created by andrei on 06.03.2018.
//

#include "full_write.h"
#include <stdbool.h>

ssize_t full_write(int fd, const void *buf, size_t count)
{
    while (true) {
        ssize_t num_written = write(fd, buf, count);
        if (num_written == -1) {
            return num_written;
        }
        count -= num_written;
        if (count == 0) {
            return num_written;
        }
        buf += num_written;
    }
}
