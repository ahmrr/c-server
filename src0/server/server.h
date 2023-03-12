#include <stdlib.h>
#include <netinet/in.h>

#ifndef SERVER_H_
#define SERVER_H_

typedef unsigned char byte;

// * serve send_buffer infinitely to address specified by sockaddr_in address
void serve(struct sockaddr_in address, byte *send_buffer, int buffer_length);
// * read file into a buffer, and return size of file
long read_file(char *filename, byte *send_buffer, int buffer_length);

#endif