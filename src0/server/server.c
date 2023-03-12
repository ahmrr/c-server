#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"
#include "const.h"
#include "http.h"

void serve(struct sockaddr_in address, packet_t packet)
{
    // * init variables
    const int MAX_RECEIVE = 1024;
    socklen_t address_size = sizeof(address);
    byte receive_buffer[MAX_RECEIVE];
    char ip_address[INET_ADDRSTRLEN];
    // * parse IP address to standard human-readable format
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

        // * get client connection's IP
        inet_ntop(AF_INET, &(address.sin_addr), ip_address, INET_ADDRSTRLEN);

        // * read from connection
        int bytes_read = read(client_socket, receive_buffer, MAX_RECEIVE);

        // * send the specified packet to the client
        char *bytes = make_packet(packet);
        send(client_socket, bytes, MAX_PACKET_SIZE, 0);

        // * closing the connected socket
        close(client_socket);

        printf(" ⟩- handled client connecting from %s\n", ip_address);
    }

    // * closing the listening socket
    shutdown(server_socket, SHUT_RDWR);

    printf("⟩- closed server connection\n");
}

long read_file(char *filename, byte *file_buffer, int buffer_length)
{
    FILE *infile = fopen(filename, "rb");
    // fseek(infile, 0L, SEEK_END);
    // int file_length = ftell(infile);
    // rewind(infile);
    fread(file_buffer, 1, buffer_length, infile);
    return ftell(infile);
}