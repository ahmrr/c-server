#include <string.h>

#include "../include/http.h"

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
    // * otherwise, if file type is unknown or TXT file
    else
        return "text/plain";
}

char *make_status(int status)
{
    switch (status)
    {
    case 200:
        return "HTTP/1.1 200 OK";
    case 300:
        return "HTTP/1.1 300 Multiple Choices";
    case 400:
        return "HTTP/1.1 400 Bad Request";
    case 401:
        return "HTTP/1.1 401 Unauthorized";
    case 403:
        return "HTTP/1.1 403 Forbidden";
    case 404:
        return "HTTP/1.1 404 Not Found";
    case 413:
        return "HTTP/1.1 413 Content Too Large";
    case 414:
        return "HTTP/1.1 414 URI Too Long";
    case 418:
        return "HTTP/1.1 418 I'm a teapot ";
    case 429:
        return "HTTP/1.1 429 Too Many Requests";
    case 431:
        return "HTTP/1.1 431 Request Header Fields Too Large";
    case 500:
        return "HTTP/1.1 500 Internal Server Error";
    case 501:
        return "HTTP/1.1 501 Not Implemented";
    case 502:
        return "HTTP/1.1 502 Bad Gateway";
    case 503:
        return "HTTP/1.1 503 Service Unavailable";
    case 504:
        return "HTTP/1.1 504 Gateway Timeout";
    case 505:
        return "HTTP/1.1 505 HTTP Version Not Supported";
    }

    return "";
}