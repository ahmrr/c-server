#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "server.h"

const int MAX_FILE_SIZE = 4096;
const int MAX_INT_SIZE = 16;

const char ADDRESS[] = "0.0.0.0";
const int DEFAULT_PORT = 5555;

// const char WEBPAGE[] =
//     "HTTP/1.1 200 OK\n"
//     "Date: Mon, 23 May 2005 22:38:34 GMT\n"
//     "Content-Type: text/html; charset=UTF-8\n"
//     "Content-Length: 155\n"
//     "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n"
//     "Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\n"
//     "ETag: \"3f80f-1b6-3e1cb03b\"\n"
//     "Accept-Ranges: bytes\n"
//     "Connection: close\n\n"
//     "<html>"
//     "  <head>"
//     "    <title>An Example Page</title>"
//     "  </head>"
//     "  <body>"
//     "    <p>Hello World, this is a very simple HTML document.</p>"
//     "  </body>"
//     "</html>";

const int TEMPLATE_SIZE = 269;
const char TEMPLATE[] =
    "HTTP/1.1 200 OK\n"
    "Date: Mon, 23 May 2005 22:38:34 GMT\n"
    "Content-Type: text/html; charset=UTF-8\n"
    "Content-Length: %d\n"
    "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n"
    "Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\n"
    "ETag: \"3f80f-1b6-3e1cb03b\"\n"
    "Accept-Ranges: bytes\n"
    "Connection: close\n\n";

const int MAX_PACKET_SIZE = MAX_FILE_SIZE + TEMPLATE_SIZE + MAX_INT_SIZE;

int main(int argc, char *argv[])
{
    // * assert command line arguments were entered
    if (argc < 3)
    {
        printf("usage: ./serve <port> <file>\n");
        return 1;
    }

    // * read in file to serve
    char *file_buffer = malloc(MAX_FILE_SIZE);
    printf("\nreading file...\n");
    int file_length = read_file(argv[2], file_buffer, MAX_FILE_SIZE);

    // * create packet to send to client
    printf("creating packet...\n");
    char *webpage = malloc(MAX_PACKET_SIZE);
    memcpy(webpage, TEMPLATE, strlen(TEMPLATE));
    memcpy(webpage + strlen(TEMPLATE), file_buffer, file_length);
    char *packet = malloc(MAX_PACKET_SIZE);
    sprintf(packet, webpage, file_length);
    free(webpage);

    // * define address to connect to and serve from that address
    printf("serving file \"%s\"...\n", argv[2]);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ADDRESS);
    address.sin_port = htons(atoi(argv[1]));
    serve(address, packet, strlen(packet));

    // * free memory
    free(packet);
    free(file_buffer);
}