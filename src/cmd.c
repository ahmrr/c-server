#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "cmd.h"
#include "const.h"

options_t options = {0};

// * all valid flags, with their corresponding handler function pointers
const flag_t flags[] = {
    (flag_t){{"-help", "-h", "--help", "--h"}, &help_handler, false},
    (flag_t){{"-port", "-p", "--port", "--p"}, &port_handler, true},
    (flag_t){{"-ip", "-i", "--ip", "--i"}, &ip_handler, true},
    (flag_t){{"-file", "-f", "--file", "--f"}, &file_handler, true},
    (flag_t){{"-load", "-l", "--load", "--l"}, &load_handler, false},
    // ! BETA
    // (flag_t){{"-config", "-c", "--config", "--c"}, &config_handler},
};

int parse_arguments(int argc, char *argv[])
{
    // * initialize options
    options.address.sin_family = AF_INET;
    options.address.sin_addr.s_addr = inet_addr(DEFAULT_IP);
    options.address.sin_port = htons(atoi(DEFAULT_PORT));
    options.path = "index.html";

    for (int i = 1; i < argc; i++)
    {
        // * obtain the current "flag"
        flag_t flag = get_flag(argv[i]);
        handler_t handler = flag.handler;
        // * if the handler exists (flag is valid)
        if (handler != NULL)
        {
            int status;

            // * if there is a flag without an argument, call the handler with value ""
            // * (and let the handler decide what to do)
            if (i == argc - 1)
                status = handler("");
            // * otherwise, call the handler for the function and increment the counter if the flag takes an argument
            else
            {
                if (flag.arg)
                    status = handler(argv[++i]);
                else
                    status = handler("");
            }

            // * fail and exit if the status wasn't positive
            if (status != EXIT_SUCCESS)
                return EXIT_FAILURE;
        }
        // * otherwise, error and exit
        else
        {
            printf("Error: invalid flag \"%s\".\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

flag_t get_flag(char *flag)
{
    // * iterate over every struct of valid flags; if the flag exists in the struct's
    // * "variations" array, return the flag
    for (int i = 0; i < (int)(sizeof(flags) / sizeof(flag_t)); i++)
        if (!strcmp(flags[i].variations[0], flag) ||
            !strcmp(flags[i].variations[1], flag) ||
            !strcmp(flags[i].variations[2], flag) ||
            !strcmp(flags[i].variations[3], flag))
            return flags[i];

    // * if no handler was found for the given flag, return an erroring value (0)
    return (flag_t){0};
}

int help_handler(char *arg)
{
    // * if a flag argument was given, error and exit (since we don't need an argument)
    if (strcmp(arg, "") != 0)
    {
        printf("Error: no flag argument expected, yet argument \"%s\" was specified for help flag.\n", arg);
        return EXIT_FAILURE;
    }

    // * print the help message
    printf("Command: ./serve [FLAGS, ARGUMENTS]\n"
           "Summary:\n"
           "    Use flags -ip and -port (or -i and -p) to specify an IP and port to serve from.\n"
           "    Use -config (or -c) to specify a configuration file that contains predefined flags and their values.\n"
           "    Use -help (or -h) for more information. Any flag that works with a single hyphen will work with two as well.\n"
           "Examples:\n"
           "    ./serve --help\n"
           "    ./serve -p 5555 -f home.html\n"
           "    ./serve -c .config\n"
           "Flags:\n"
           "    -help, -h, --help, --h\n"
           "        Display this message\n"
           "        Argument:           No\n"
           "    -port, -p, --port, -p\n"
           "        Specify port to serve from\n"
           "        Argument:           Yes\n"
           "        Default value:      8080\n"
           "        Flag usage:         ./serve -p 5555\n"
           "    -ip, -i, --ip, --i\n"
           "        Specify IP address to serve from\n"
           "        Argument:           Yes\n"
           "        Default value:      127.0.0.1\n"
           "        Flag usage:         ./serve -i 0.0.0.0\n"
           "    -file, -f, --file, --f\n"
           "        Specify file to serve\n"
           "        Argument:           Yes\n"
           "        Default value:      index.html\n"
           "        Flag usage:         ./serve -f home.html\n"
           "    -config, -c, --config, --c\n"
           "        Specify config file\n"
           "        Argument:           Yes\n"
           "        Default value:      index.html\n"
           "        Flag usage:         ./serve -f home.html\n");

    return EXIT_SUCCESS;
}

int port_handler(char *arg)
{
    // * if a flag argument was not given, error and exit (since we need an argument)
    if (strcmp(arg, "") == 0)
    {
        printf("Error: no flag argument given for port flag.\n");
        return EXIT_FAILURE;
    }

    options.address.sin_port = htons(atoi(arg));

    return EXIT_SUCCESS;
}

int ip_handler(char *arg)
{
    // * if a flag argument was not given, error and exit (since we need an argument)
    if (strcmp(arg, "") == 0)
    {
        printf("Error: no flag argument given for IP flag.\n");
        return EXIT_FAILURE;
    }

    options.address.sin_addr.s_addr = inet_addr(arg);

    return EXIT_SUCCESS;
}

int file_handler(char *arg)
{
    // * if a flag argument was not given, error and exit (since we need an argument)
    if (strcmp(arg, "") == 0)
    {
        printf("Error: no flag argument given for file flag.\n");
        return EXIT_FAILURE;
    }

    options.path = arg;

    return EXIT_SUCCESS;
}

int load_handler(char *arg)
{
    // * if a flag argument was given, error and exit (since we don't need an argument)
    if (strcmp(arg, "") != 0)
    {
        printf("Error: no flag argument expected, yet argument \"%s\" was specified for help flag.\n", arg);
        return EXIT_FAILURE;
    }

    options.buffered = true;

    return EXIT_SUCCESS;
}

// ! BETA
/*
int config_handler(char *arg)
{
    // * if a flag argument was not given, error and exit (since we need an argument)
    if (strcmp(arg, "") == 0)
    {
        printf("Error: no flag argument given for config flag.\n");
        return EXIT_FAILURE;
    }

    // * try open file specified by arg; if some error happened, error and exit
    FILE *infile = fopen(arg, "rb");
    if (infile == NULL)
    {
        printf("Error: could not open config file \"%s\"; file might not exist.\n", arg);
        return EXIT_FAILURE;
    }
    char c = 0;

    // * arg variable to store flags and values, as well as argv_s to store current argument size and argv_i to size of argument string
    char *arg = malloc(8);
    int arg_i = 0;
    int arg_s = 8;
    bool next_is_flag = true;

    // * read file character-by-character
    while ((c = fgetc(infile)) != EOF)
    {
        // * if a newline or space is detected, reset variables as necessary and call
        if (c == '\n' || c == ' ')
        {
            arg_i = 0;

            if (next_is_flag)
            {
                // * obtain the handler for the current "flag"
                handler_t handler = get_handler(arg);
                // * if the handler exists (flag is valid)
                if (handler != NULL)
                {
                    int status;

                    // * if there is a flag without an argument, call the handler with value ""
                    // * (and let the handler decide what to do)
                    if (arg_i == arg_s - 1)
                        status = handler("");
                    // * otherwise, call the handler for the function and increment the counter (since the next argument isn't a flag)
                    else
                        status = handler(argv[++i]);

                    // * fail and exit if the status wasn't positive
                    if (status != EXIT_SUCCESS)
                        return EXIT_FAILURE;
                }
                // * otherwise, error and exit
                else
                {
                    printf("Error: invalid flag \"%s\".\n", argv[i]);
                    return EXIT_FAILURE;
                }
            }
        }
        else
        {
        }
    }

    // * free malloc'ed value(s)
    free(arg);

    return EXIT_SUCCESS;
}
*/