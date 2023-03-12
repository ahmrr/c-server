#include <netinet/in.h>

#ifndef SERVER_H_
#define SERVER_H_

// * serve a file from a specified address
void serve_file(struct sockaddr_in address, char *file);
// * serve a directory from a specified address
void serve_directory(struct sockaddr_in address, char *dir);

#endif