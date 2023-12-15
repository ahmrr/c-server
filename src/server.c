#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/sendfile.h>

#include "http.h"
#include "util.h"
#include "const.h"
#include "server.h"

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
    char receive_buffer[MAX_RECEIVE];

    struct sockaddr_in client_address = {0};
    socklen_t client_address_len = sizeof(client_address);
    char client_ip[INET_ADDRSTRLEN];
    int in_file = open(file, O_RDONLY);

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

    // * get size of payload
    packet.payload_len = file_size(file);

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

    // * form bytes that correspond to the HTTP status and header
    size_t send_buffer_size = packet.status_len + packet.header_len;
    char *send_buffer = malloc(send_buffer_size);
    memcpy(send_buffer, packet.status, packet.status_len);
    memcpy(send_buffer + packet.status_len, packet.header, packet.header_len);

    // * repeat until we no longer want to serve
    while (keep_serving)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_address_len);
        inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);

        printf("Client connecting from %s\n", client_ip);

        ssize_t bytes_read = read(client_socket, receive_buffer, MAX_RECEIVE);

        if (bytes_read == 0)
            printf(" - Client sent nothing; terminating connection\n");
        else
        {
            struct Request request = parse_request(receive_buffer);
            printf(" - Client wants to %s %s via %s\n", request.method, request.endpoint, request.http_version);
            if (strcmp(request.endpoint + 1, file) != 0 && strcmp(request.endpoint + 1, "/favicon.ico") != 0)
            {
                printf(" - Resource does not exist; returning 404\n");
                // * 2 -> 2 bytes of format specifiers
                // * 30 -> length of date
                char *send_buffer_404 = malloc(sizeof(RESPONSE_404) - 2 + 30);
                // sprintf(send_buffer_404, RESPONSE_404, make_date()
                // send(client_socket, )
            }

            clock_t start = clock();

            send(client_socket, send_buffer, send_buffer_size, 0);
            sendfile(client_socket, in_file, 0, packet.payload_len);

            clock_t end = clock();

            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

            printf(" - Took %lf msec to send the packet\n", time_taken * 1000);
        }

        close(client_socket);

        printf("Closed client connection\n");
    }

    // * close the listening socket
    shutdown(server_socket, SHUT_RDWR);

    printf("Shut down server\n");

    // * free memory allocated for the packet
    free(packet.header);
    free(send_buffer);

    close(in_file);

    return EXIT_SUCCESS;
}

int serve_file_buffered(struct sockaddr_in address, char *file)
{
    const time_t timer = time(NULL);

    // * initialize variables
    const int MAX_RECEIVE = 4096;
    char receive_buffer[MAX_RECEIVE];

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

        printf("Client connecting from %s\n", client_ip);

        ssize_t bytes_read = read(client_socket, receive_buffer, MAX_RECEIVE);

        if (bytes_read == 0)
            printf(" - Client sent nothing; terminating connection\n");
        else
        {
            struct Request request = parse_request(receive_buffer);
            printf(" - Client wants to %s %s via %s\n", request.method, request.endpoint, request.http_version);

            clock_t start = clock();

            send(client_socket, send_buffer, send_buffer_size, 0);

            clock_t end = clock();

            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

            printf(" - Took %lf msec to send the packet\n", time_taken * 1000);
        }

        close(client_socket);

        printf("Closed client connection\n");
    }

    // * close the listening socket
    shutdown(server_socket, SHUT_RDWR);

    printf("Shut down server\n");

    // * free memory allocated for the packet
    free(packet.header);
    free(packet.payload);
    free(send_buffer);

    return EXIT_SUCCESS;
}

int serve_directory(struct sockaddr_in address, char *dir)
{
    return EXIT_SUCCESS;
}