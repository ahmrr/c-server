#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../include/cmd.h"
#include "../include/util.h"
#include "../include/const.h"

int main(int argc, char *argv[])
{
    time_t timer = time(NULL);
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

    // ! working on this
    struct tm current_time = *localtime(&timer);

    // * obtain the path mode for the given path
    mode_t mode = path_mode(options.file);
    // * if the mode is invalid (the path doesn't exist, most likely), error and exit
    if (mode == (mode_t)-1)
    {
        printf("Error: failure in reading mode of path \"%s\"; it may not exist.\n", options.file);
        return EXIT_FAILURE;
    }

    printf("file mode: %d\n", mode);

    // * if the path specified is a regular file
    if (S_ISREG(mode))
    {
        printf("regular file\n");
    }
    // * otherwise, if the path specified is a directory
    else if (S_ISDIR(mode))
    {
        printf("directory\n");
    }
    // * otherwise, error and exit
    else
    {
        printf("Error: unknown path type \"%s\"; only regular files and directories are allowed.\n", options.file);
        return EXIT_FAILURE;
    }

    printf("Serving \"%s\" from IP %s and port %d\n", options.file, ip_address, ntohs(options.address.sin_port));

    return EXIT_SUCCESS;
}