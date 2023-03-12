#include <stdlib.h>

#include "server.h"
#include "const.h"

#ifndef HTTP_H_
#define HTTP_H_

typedef struct Packet
{
    char status[MAX_STATUS_SIZE];
    char header[MAX_HEADER_SIZE];
    char payload[MAX_PAYLOAD_SIZE];
} packet_t;

// * convert struct Packet into a sendable packet
char *make_packet(packet_t data);
// * get content type based on filename
char *get_content_type(char *filename);

#endif