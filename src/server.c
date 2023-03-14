#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/http.h"
#include "../include/util.h"
#include "../include/const.h"
#include "../include/server.h"

bool volatile keep_serving = true;

int handle_request(char *request)
{
    return EXIT_SUCCESS;
}

int serve_file(struct sockaddr_in address, char *file)
{
    const time_t timer = time(NULL);

    // * initialize variables
    const int MAX_RECEIVE = 4096;
    byte receive_buffer[MAX_RECEIVE];

    struct sockaddr_in client_address = {0};
    socklen_t client_address_len = sizeof(client_address);
    char client_ip[INET_ADDRSTRLEN];

    // * initialize server socket and socket options
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int server_socket_opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &server_socket_opt, sizeof(server_socket_opt));

    // * bind the socket to port and listen for clients
    bind(server_socket, (struct sockaddr *)&address, sizeof(address));
    listen(server_socket, MAX_CLIENTS);

    // * initialize packet, and generate a status line for it
    packet_t packet = {0};
    packet.status = make_status(200);
    packet.status_len = strlen(packet.status);

    // * read in file to packet
    packet.payload_len = read_file(file, &(packet.payload));

    char *content_type = get_content_type(file);
    struct tm current_time = *localtime(&timer);
    char date[31] = {0};
    make_date(date, current_time);

    // * 7 -> 7 bytes of format specifiers
    // * 30 -> length of date
    packet.header_len = strlen(HEADER_TEMPLATE) - 7 + 30 + strlen(content_type) + digits(packet.payload_len);
    packet.header = malloc(packet.header_len);

    // * fill out the "fields" of the packet's header
    sprintf(packet.header, HEADER_TEMPLATE, date, content_type, packet.payload_len);

    // * form bytes that correspond to the HTTP packet
    size_t send_buffer_size = packet.status_len + packet.header_len + packet.payload_len;
    char *send_buffer = malloc(send_buffer_size);
    memcpy(send_buffer, packet.status, packet.status_len);
    memcpy(send_buffer + packet.status_len, packet.header, packet.header_len);
    memcpy(send_buffer + packet.status_len + packet.header_len, packet.payload, packet.payload_len);

    // * repeat until we no longer want to serve
    while (keep_serving)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_len);
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

        ssize_t bytes_read = read(client_socket, receive_buffer, MAX_RECEIVE);

        send(client_socket, send_buffer, send_buffer_size, 0);

        close(client_socket);

        printf(" - Handled client from %s; they sent %ld bytes\n", client_ip, bytes_read);
    }

    // * close the listening socket
    shutdown(server_socket, SHUT_RDWR);

    printf("Shut down server\n");

    // * free memory allocated for the packet
    free(packet.header);
    free(packet.payload);

    return EXIT_SUCCESS;
}

int serve_directory(struct sockaddr_in address, char *dir)
{
    return EXIT_SUCCESS;
}