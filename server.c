#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"

const int MAX_CLIENTS = 8;

void serve(struct sockaddr_in address, byte *file_buffer, int buffer_length)
{
    socklen_t address_size = sizeof(address);
    byte buffer[1024];
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address.sin_addr), ip_address, INET_ADDRSTRLEN);

    printf("⟩- maximum clients:\t%d\n", MAX_CLIENTS);
    printf("⟩- address:\t\t%s\n", ip_address);
    printf("⟩- port:\t\t%d\n", ntohs(address.sin_port));

    // * initialize handle to server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // * set socket options
    int server_socket_opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,
               &server_socket_opt, sizeof(server_socket_opt));

    // * bind handle to address
    bind(server_socket, (struct sockaddr *)&address, sizeof(address));

    // * listen for the maximum number of clients on the server socket
    listen(server_socket, MAX_CLIENTS);

    // * accept connection
    while (1)
    {
        // * accept a client connection
        int client_socket = accept(server_socket, (struct sockaddr *)&address,
                                   (socklen_t *)&address_size);

        // * read from connection
        int bytes_read = read(client_socket, buffer, 1024);

        // * send a hello message to the port
        send(client_socket, file_buffer, buffer_length, 0);

        // * closing the connected socket
        close(client_socket);

        printf(" ⟩- handled client; file descriptor is %d\n", client_socket);
    }

    // * closing the listening socket
    shutdown(server_socket, SHUT_RDWR);

    printf("⟩- closed server connection\n");
}

int read_file(char *filename, byte *file_buffer, int buffer_length)
{
    FILE *infile = fopen(filename, "rb");
    fseek(infile, 0L, SEEK_END);
    int file_length = ftell(infile);
    rewind(infile);
    fread(file_buffer, 1, buffer_length, infile);
    return file_length;
}