#include <stdbool.h>

#include "const.h"

#ifndef CONFIG_H_
#define CONFIG_H_

struct Config
{
    char **files;
    size_t files_len;
    bool buffered;
    int threads;
    int port;
};

#define DEFAULT_CONFIG ((struct Config){NULL, 0, true, 1, 8080})

/**
 * @brief Parse config file to get settings
 *
 * @param config_file
 * @return struct Config
 */
struct Config parse_config(const char *config_filename);

#endif
