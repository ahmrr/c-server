#include <netinet/in.h>

#ifndef CONST_H_
#define CONST_H_

#define DEFAULT_PORT "8080"
#define DEFAULT_IP "127.0.0.1"

typedef unsigned char byte;
typedef unsigned long size;

// * function pointer to a handler function
typedef int (*handler_t)(char *arg);

// * stores command flag information
typedef struct Flag
{
    char *variations[4];
    handler_t handler;
} flag_t;

// * stores program options (exactly 3 bytes in size)
typedef struct Options
{
    struct sockaddr_in address;
    char *file;
} options_t;

// * external options variable; defined in file src/cmd.c
extern options_t options;

#endif
