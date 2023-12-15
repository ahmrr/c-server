#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "util.h"

mode_t path_mode(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == -1)
        return -1;

    return path_stat.st_mode;
}

size_t read_file(const char *file, char **bytes)
{
    const size_t ALLOC_BLOCK = 64;

    FILE *in = fopen(file, "rb");
    if (in == NULL)
    {
        printf("Error: could not read file \"%s\"; it may not exist.\n", file);
        return -1;
    }

    size_t bytes_size = ALLOC_BLOCK;
    size_t bytes_index = 0;
    *bytes = malloc(bytes_size);

    size_t bytes_read = ALLOC_BLOCK;
    while (bytes_read == ALLOC_BLOCK)
    {
        // * reallocate another block of memory for reading in
        char *_bytes = realloc(*bytes, bytes_size += ALLOC_BLOCK);
        *bytes = _bytes;

        // ! DEBUG
        // printf("bytes_read is %lu\nbytes_size is %lu\nbytes_index is %lu\n", bytes_read, bytes_size, bytes_index);

        // * read in more bytes from the file, and update the index
        bytes_read = fread(*bytes + bytes_index, 1, ALLOC_BLOCK, in);
        bytes_index += bytes_read;
    }

    fclose(in);

    return bytes_index;
}

int digits(size_t num)
{
    if (num < 10UL)
        return 1;
    if (num < 100UL)
        return 2;
    if (num < 1000UL)
        return 3;
    if (num < 10000UL)
        return 4;
    if (num < 100000UL)
        return 5;
    if (num < 1000000UL)
        return 6;
    if (num < 10000000UL)
        return 7;
    if (num < 100000000UL)
        return 8;
    if (num < 1000000000UL)
        return 9;
    if (num < 10000000000UL)
        return 10;
    if (num < 100000000000UL)
        return 11;
    if (num < 1000000000000UL)
        return 12;
    if (num < 10000000000000UL)
        return 13;
    if (num < 100000000000000UL)
        return 14;
    if (num < 1000000000000000UL)
        return 15;
    if (num < 10000000000000000UL)
        return 16;
    if (num < 100000000000000000UL)
        return 17;
    if (num < 1000000000000000000UL)
        return 18;
    if (num < 10000000000000000000UL)
        return 19;
    else
        return 20;
}

size_t file_size(const char *file)
{
    FILE *in = fopen(file, "rb");
    fseek(in, 0L, SEEK_END);
    size_t size = ftell(in);
    fclose(in);
    return size;
}

int atoin(const char *str, int n)
{
    int neg = *str == '-';
    int acc = neg ? 0 : *str - '0';
    for (int i = 1; i < n; i++)
        acc = acc * 10 + str[i] - '0';
    return neg ? -acc : acc;
}

int atobn(const char *str, int n)
{
    if (n == 4)
        return strncmp(str, "true", n) ? -1 : 1;
    else if (n == 5)
        return strncmp(str, "true", n) ? (strncmp(str, "false", n) ? -1 : 0) : 1;
    else
        return -1;
}

// int atoil(const char *str, char c)
// {
//     int neg = *str == '-';
//     int acc = neg ? 0 : *str - '0';
//     while (*++str != c)
//         acc = acc * 10 + *str - '0';
//     return neg ? -acc : acc;
// }