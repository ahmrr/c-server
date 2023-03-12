#ifndef CONST_H_
#define CONST_H_

// * the maximum size a file (packet payload) can have
#define MAX_PAYLOAD_SIZE 4096
// * the maximum total size the status line (1st line) of an HTTP packet can have
#define MAX_STATUS_SIZE 32
// * the maximum total size the header of an HTTP packet can have
#define MAX_HEADER_SIZE 512
// * the maximum bytes the Content-Length header's value can have
#define MAX_CL_SIZE 16
// * the maximum total size a packet can have
#define MAX_PACKET_SIZE MAX_STATUS_SIZE + MAX_HEADER_SIZE + MAX_PAYLOAD_SIZE
// * the maximum number of clients that can be connected at one time
#define MAX_CLIENTS 8

// * the default address and port
#define DEFAULT_ADDRESS "0.0.0.0"
#define DEFAULT_PORT 5555

// * the HTTP packet template
// const int PACKET_TEMPLATE_SIZE = 269;
// const char PACKET_TEMPLATE[] =
//     "HTTP/1.1 200 OK\n"
//     "Date: Mon, 23 May 2005 22:38:34 GMT\n"
//     "Content-Type: text/html; charset=UTF-8\n"
//     "Content-Length: %d\n"
//     "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n"
//     "Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\n"
//     "ETag: \"3f80f-1b6-3e1cb03b\"\n"
//     "Accept-Ranges: bytes\n"
//     "Connection: close\n\n";

#define DEFAULT_STATUS "HTTP/1.1 200 OK"
// * the default header. 1st arg: [string] date, 2nd arg: [string] content-type, 3rd arg: [int] content-length
#define DEFAULT_HEADER                        \
    "Date: %s\n"                              \
    "Content-Type: %s; charset=UTF-8\n"       \
    "Content-Length: %d\n"                    \
    "Server: C-Server/0.1.0 (Ubuntu/Linux)\n" \
    "Accept-Ranges: bytes\n"                  \
    "Connection: close"

#endif