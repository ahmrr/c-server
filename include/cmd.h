#include "const.h"

#ifndef CMD_H_
#define CMD_H_

// * parses arguments and calls the appropriate handlers
int parse_arguments(int argc, char *argv[]);
// * obtains handler for a specific flag (returns NULL if handler doesn't exist)
handler_t get_handler(char *flag);

// * handles a "help" flag
int help_handler(char *arg);
// * handles a "port" flag
int port_handler(char *arg);
// * handles an "ip" flag
int ip_handler(char *arg);
// * handles a "file" flag
int file_handler(char *arg);

// ! BETA
// * handles a "config" flag
// int config_handler(char *arg);

// * Stores program options (exactly 3 bytes in size)
typedef struct Options
{
    struct sockaddr_in address;
    char *path;
} options_t;

// * External options variable; defined in file src/cmd.c
extern options_t options;

#endif