#include <time.h>
#include <stdlib.h>

#include "server.h"
#include "const.h"

#ifndef HTTP_H_
#define HTTP_H_

// * Packet type
typedef struct Packet
{
    char *status;
    char *header;
    char *payload;
    size_t status_len;
    size_t header_len;
    size_t payload_len;
} packet_t;

struct Request
{
    char *method;
    char *endpoint;
    char *http_version;
};

// ! BETA
/**
 * @brief Convert struct Packet into a sendable packet
 *
 * @param data the packet to compress into a packet
 * @return The dynamically allocated packet string (char*)
 */
// char *make_packet(packet_t data);
/**
 * @brief Get HTTP content type of file based on filename
 *
 * @param filename the file to analyze
 * @return The content type of the given file
 */
char *get_content_type(char *filename);
/**
 * @brief Make the HTTP status of the given struct Packet
 *
 * @param data a pointer to the packet whose status field needs to be made
 */
char *make_status(int status);
/**
 * @brief Make the HTTP-formatted date based on current_time and store it in dest
 *
 * @param dest a char array of length at least 31
 * @param current_time the current time
 */
void make_date(char *dest, struct tm current_time);
/**
 * @brief Get the method, endpoint, and HTTP version of an HTTP request
 *
 * @param packet the packet to parse
 *
 * @return The request information of the packet
 */
struct Request parse_request(char *packet);

#define HEADER_TEMPLATE                       \
    "Date: %s\n"                              \
    "Content-Type: %s; charset=UTF-8\n"       \
    "Content-Length: %lu\n"                   \
    "Server: C-Server/0.1.0 (Ubuntu/Linux)\n" \
    "Connection: close\n"                     \
    "Access-Control-Allow-Origin: *\n\n"

#define RESPONSE_404                           \
    "HTTP/1.1 404 Not Found\n"                 \
    "Date: %s\n"                               \
    "Content-Type: text/html; charset=UTF-8\n" \
    "Content-Length: 82\n"                     \
    "Server: C-Server/0.1.0 (Ubuntu/Linux)\n"  \
    "Connection: close\n"                      \
    "Access-Control-Allow-Origin: *\n\n"       \
    "<html><head><title>404</title></head><body><h1>404: Resource Not Found</h1></html>"

#endif