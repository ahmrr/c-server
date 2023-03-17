#include "const.h"

#ifndef CMD_H_
#define CMD_H_

/**
 * @brief Parses arguments and calls the appropriate handlers
 *
 * @param argc the argc passed into the main function
 * @param argv the arguments passed into the main function
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int parse_arguments(int argc, char *argv[]);
/**
 * @brief Obtain a specific flag's struct representation
 *
 * @param flag the flag to obtain a handler for
 * @return The corresponding handler, or {0} if it doesn't exist
 */
flag_t get_flag(char *flag);

/**
 * @brief Handles a "help" flag
 *
 * @param arg the argument passed to the flag (next value in the argument list); must be equal to ""
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int help_handler(char *arg);
/**
 * @brief Handles a "port" flag
 *
 * @param arg the argument passed to the flag (next value in the argument list)
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int port_handler(char *arg);
/**
 * @brief Handles an "ip" flag
 *
 * @param arg the argument passed to the flag (next value in the argument list)
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int ip_handler(char *arg);
/**
 * @brief Handles a "file" flag
 *
 * @param arg the argument passed to the flag (next value in the argument list)
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int file_handler(char *arg);
/**
 * @brief Handles a "load" flag
 *
 * @param arg the argument passed to the flag (next value in the argument list); must be equal to ""
 * @return Status (either EXIT_FAILURE or EXIT_SUCCESS)
 */
int load_handler(char *arg);

// ! BETA
// * handles a "config" flag
// int config_handler(char *arg);

// * Stores program options
typedef struct Options
{
    struct sockaddr_in address;
    char *path;
    bool buffered;
} options_t;

// * External options variable; defined in file src/cmd.c
extern options_t options;

#endif