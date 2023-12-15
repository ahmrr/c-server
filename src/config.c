#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"
#include "config.h"

struct Config parse_config(const char *config_filename)
{
    printf("parsing\n");
    FILE *config_file = fopen(config_filename, "r");
    if (!config_file)
        return (struct Config){0};

    struct Config config = DEFAULT_CONFIG;

    char buf[4096];
    memset(buf, 0, 4096);
    int buf_len = fread(&buf, 1, 4096, config_file);

    // char *param_start = buf, *param_stop, *val_start, *val_stop;

    // while (val_stop = strtok(param_start, "\n"))
    // {
    //     // * trim leading whitespace
    //     while (isspace(++param_start))
    //         ;
    //     param_stop = param_start;

    //     // * find equals sign
    //     while (param_stop != "=")
    //         param_stop++;
    //     val_start = param_stop;

    //     // * trim trailing param and leading val whitespace
    //     while (isspace(--param_stop))
    //         ;
    //     while (isspace(++val_start))
    //         ;

    //     // * trim trailing whitespace
    //     while (isspace(--val_stop))
    //         ;

    //     param_start = val_stop;
    // }

    char *param_start = buf, *param_stop, *val_start, *val_stop = strstr(param_start, "\n");

    while (val_stop)
    {
        param_stop = param_start;

        // * find equals sign
        while (*param_stop != '=')
            param_stop++;
        val_start = param_stop + 1;

        // * assign to correct config fields
        int param_len = param_stop - param_start;
        int val_len = val_stop - val_start;
        if (!strncmp(param_start, "files", param_len))
        {
            printf("files\n");
            char *file;
            config.files = malloc(0);
            while (file = strtok(val_start, ","))
            {
                char **new = realloc(config.files, (++config.files_len) * sizeof(char **));
                if (new)
                    config.files = new;
                printf("reallocated\n");

                char *end = strstr(file, ",");
                int len = end ? end - file : strstr(file, "\n") - file;

                config.files[config.files_len - 1] = malloc(len + 1);
                memcpy(&config.files[config.files_len - 1], file, len);
                printf("copied\n");
                printf("len %d\n", len);
                printf("%.*s\n", len, config.files[config.files_len - 1]);
                // printf("%s,", config.files[config.files_len - 1]);
                config.files[config.files_len - 1][len] = 0;
            }
        }
        else if (!strncmp(param_start, "buffered", param_len))
            config.buffered = atobn(val_start, val_len);
        else if (!strncmp(param_start, "threads", param_len))
            config.threads = atoin(val_start, val_len);
        else if (!strncmp(param_start, "port", param_len))
            config.port = atoin(val_start, val_len);

        param_start = val_stop + 1;
        char *find = strstr(param_start, "\n");
        if (val_stop != buf + buf_len)
            val_stop = find ? find : buf + buf_len;
        else
            val_stop = NULL;
    }
}