#include <stdlib.h>
#include <string.h>

#include "http.h"

char *make_packet(packet_t data)
{
    // * create packet and initialize it
    char *packet = calloc(MAX_PACKET_SIZE, 1);

    // * copy packet information over
    memcpy(packet, &data.status, strlen(data.status));
    packet[strlen(data.status)] = '\n';
    memcpy(packet + strlen(data.status) + 1, &data.header, strlen(data.header));
    packet[strlen(data.header)] = packet[strlen(data.header) + 1] = '\n';
    memcpy(packet + strlen(data.status) + 1 + strlen(data.header) + 2, &data.payload, strlen(data.payload));

    return packet;
}

char *get_content_type(char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";

    // * if file is HTML
    if (strcmp(dot, ".html") == 0)
        return "text/html";
    // * if file is JSON
    else if (strcmp(dot, ".json") == 0)
        return "application/json";
    // * otherwise, if file type is unknown
    else
        return "text/plain";
}