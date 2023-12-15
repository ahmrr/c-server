#include "const.h"

#ifndef UTIL_H_
#define UTIL_H_

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

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
 * @brief Return the number of digits in a number
 *
 * @param num the number to count
 * @return The number of digits in the number
 */
int digits(size_t num);
/**
 * @brief Return the size of a file
 *
 * @param file the file to analyze
 * @return The number of bytes in the file
 */
size_t file_size(const char *file);
/**
 * @brief Converts n chars of str to int
 *
 * @param str the string to convert
 * @param n the number of characters in str to convert
 * @return int the converted value
 */
int atoin(const char *str, int n);
/**
 * @brief Converts n chars of str to bool
 *
 * @param str the string to convert
 * @param n the number of characters in str to convert
 * @return int the converted value
 */
int atobn(const char *str, int n);

#endif