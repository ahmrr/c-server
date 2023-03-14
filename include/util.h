#include "const.h"

#ifndef UTIL_H_
#define UTIL_H_

/**
 * @brief Returns path mode for processing
 *
 * @param path the path to analyze
 * @return The mode of the path
 */
mode_t path_mode(const char *path);
/**
 * @brief Read file in to byte *bytes, with a byte limit given by size_t limit
 *
 * @param file the file to read in
 * @param bytes the pointer to store the file's bytes in; this will be malloc'ed by the function and must be free'd.
 * @return the size of the file
 */
size_t read_file(const char *file, char **bytes);
/**
 * @brief Return the number of digits in the number
 *
 * @param num the number to count
 * @return The number of digits in the number
 */
int digits(size_t num);

#endif