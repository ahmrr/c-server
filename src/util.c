#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../include/util.h"

mode_t path_mode(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == -1)
        return -1;

    return path_stat.st_mode;
}