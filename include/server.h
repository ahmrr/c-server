#include <stdbool.h>
#include <netinet/in.h>

#ifndef SERVER_H_
#define SERVER_H_

/**
 * @brief Handle an incoming request
 *
 * @param request the packet that stores the request
 * @return The status of the function; either EXIT_SUCCESS or EXIT_FAILURE.
 */
int handle_request(char *request);
/**
 * @brief Serve a single file via a TCP socket
 *
 * @param address the address to serve from
 * @param file the file to serve
 * @return The status of the function; either EXIT_SUCCESS or EXIT_FAILURE.
 */
int serve_file(struct sockaddr_in address, char *file);
/**
 * @brief Serve all files in a directory via a TCP socket
 *
 * @param address the address to serve from
 * @param dir the directory to serve
 * @return The status of the function; either EXIT_SUCCESS or EXIT_FAILURE.
 */
int serve_directory(struct sockaddr_in address, char *dir);

// * whether to keep serving file or directory; initialized in src/server.c
extern volatile bool keep_serving;

#endif