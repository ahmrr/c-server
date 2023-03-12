#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/server.h"

void serve_file(struct sockaddr_in address, char *file)
{
    socklen_t address_len = sizeof(address);
}

void serve_directory(struct sockaddr_in address, char *dir)
{
    socklen_t address_len = sizeof(address);
}