// TODO: implement file transfer using sendfile()

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../include/cmd.h"
#include "../include/util.h"
#include "../include/const.h"
#include "../include/server.h"

// void stop_serving()
// {
//     keep_serving = false;
// }

int main(int argc, char *argv[])
{
    // signal(SIGINT, stop_serving);
    /*
    if (argc <= 1)
    {
        printf("Error: no flags specified. Run ./serve --help for help on this program.\n");
        return EXIT_FAILURE;
    }
    */

    int status = parse_arguments(argc, argv);
    if (status != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // * parse IP address to standard human-readable format
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(options.address.sin_addr), ip_address, INET_ADDRSTRLEN);

    // * obtain the path mode for the given path
    mode_t mode = path_mode(options.path);
    // * if the mode is invalid (the path doesn't exist, most likely), error and exit
    if (mode == (mode_t)-1)
    {
        printf("Error: failure in reading mode of path \"%s\"; it may not exist.\n", options.path);
        return EXIT_FAILURE;
    }

    // * if the path specified is a regular file
    if (S_ISREG(mode))
    {
        printf("Serving file \"%s\" from IP %s and port %d\n", options.path, ip_address, ntohs(options.address.sin_port));

        serve_file(options.address, options.path);
    }
    // * otherwise, if the path specified is a directory
    else if (S_ISDIR(mode))
    {
        printf("Serving all files in directory \"%s\" from IP %s and port %d\n", options.path, ip_address, ntohs(options.address.sin_port));

        serve_directory(options.address, options.path);
    }
    // * otherwise, error and exit
    else
    {
        printf("Error: unknown path type \"%s\"; only regular files and directories are allowed.\n", options.path);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}