#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SERVER_H_
#define SERVER_H_

typedef unsigned char byte;

void serve(struct sockaddr_in address, byte *file_buffer, int buffer_length);
int read_file(char *filename, byte *file_buffer, int buffer_length);

#endif