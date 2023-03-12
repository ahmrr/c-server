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
} packet_t;

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

#endif