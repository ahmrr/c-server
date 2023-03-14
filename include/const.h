#include <netinet/in.h>

#ifndef CONST_H_
#define CONST_H_

#define DEFAULT_PORT "8080"
#define DEFAULT_IP "127.0.0.1"

// * The maximum size a file (packet payload) can have
#define MAX_PAYLOAD_SIZE 4096
// * The maximum total size the status line (1st line) of an HTTP packet can have
#define MAX_STATUS_SIZE 32
// * The maximum total size the header of an HTTP packet can have
#define MAX_HEADER_SIZE 512
// * The maximum bytes the Content-Length header's value can have
#define MAX_CL_SIZE 16
// * The maximum total size a packet can have
#define MAX_PACKET_SIZE MAX_STATUS_SIZE + MAX_HEADER_SIZE + MAX_PAYLOAD_SIZE
// * The maximum number of clients that can be connected at one time
#define MAX_CLIENTS 8

typedef unsigned char byte;
typedef unsigned long size;

// * Function pointer to a handler function
typedef int (*handler_t)(char *arg);

// * Stores command flag information
typedef struct Flag
{
    char *variations[4];
    handler_t handler;
} flag_t;

#endif
