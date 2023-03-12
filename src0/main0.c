// TODO: add support for file path serving
// TODO: add multithreading for clients
// TODO: add HTTP parser
// TODO: add semantically correct HTTP packet support

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server/server.h"
#include "server/const.h"
#include "server/http.h"

int main(int argc, char *argv[])
{
    time_t t = time(NULL);

    // * assert command line arguments were entered
    if (argc < 3)
    {
        printf("usage: ./serve <port> <file>\n");
        return 1;
    }

    // * read in file to serve
    char *file_buffer = malloc(MAX_PAYLOAD_SIZE);
    printf("\nreading file...\n");
    int file_length = read_file(argv[2], file_buffer, MAX_PAYLOAD_SIZE);

    // * create packet to send to client
    printf("creating packet...\n");
    // char *webpage = malloc(MAX_PACKET_SIZE);
    // memcpy(webpage, PACKET_TEMPLATE, strlen(PACKET_TEMPLATE));
    // memcpy(webpage + strlen(PACKET_TEMPLATE), file_buffer, file_length);
    // char *packet = malloc(MAX_PACKET_SIZE);
    // sprintf(packet, webpage, file_length);
    // free(webpage);
    packet_t packet = {DEFAULT_STATUS, DEFAULT_HEADER, file_buffer};
    struct tm current_time = *localtime(&t);
    sprintf(&packet.header, &packet.header, );

    // * define address to connect to and serve from that address
    printf("serving file \"%s\"...\n", argv[2]);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);
    address.sin_port = htons(atoi(argv[1]));
    serve(address, packet, strlen(packet));

    // * free memory
    free(packet);
    free(file_buffer);
}