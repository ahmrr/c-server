#include <time.h>
#include <stdio.h>
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
        return "HTTP/1.1 200 OK\n";
    case 300:
        return "HTTP/1.1 300 Multiple Choices\n";
    case 400:
        return "HTTP/1.1 400 Bad Request\n";
    case 401:
        return "HTTP/1.1 401 Unauthorized\n";
    case 403:
        return "HTTP/1.1 403 Forbidden\n";
    case 404:
        return "HTTP/1.1 404 Not Found\n";
    case 413:
        return "HTTP/1.1 413 Content Too Large\n";
    case 414:
        return "HTTP/1.1 414 URI Too Long\n";
    case 418:
        return "HTTP/1.1 418 I'm a teapot\n";
    case 429:
        return "HTTP/1.1 429 Too Many Requests\n";
    case 431:
        return "HTTP/1.1 431 Request Header Fields Too Large\n";
    case 500:
        return "HTTP/1.1 500 Internal Server Error\n";
    case 501:
        return "HTTP/1.1 501 Not Implemented\n";
    case 502:
        return "HTTP/1.1 502 Bad Gateway\n";
    case 503:
        return "HTTP/1.1 503 Service Unavailable\n";
    case 504:
        return "HTTP/1.1 504 Gateway Timeout\n";
    case 505:
        return "HTTP/1.1 505 HTTP Version Not Supported\n";
    }

    return "";
}

void make_date(char *dest, struct tm current_time)
{
    char *weekday;
    char *month;

    switch (current_time.tm_wday)
    {
    case 0:
        weekday = "Mon";
        break;
    case 1:
        weekday = "Tue";
        break;
    case 2:
        weekday = "Wed";
        break;
    case 3:
        weekday = "Thu";
        break;
    case 4:
        weekday = "Fri";
        break;
    case 5:
        weekday = "Sat";
        break;
    case 6:
        weekday = "Sun";
        break;
    }

    switch (current_time.tm_mon)
    {
    case 0:
        month = "Jan";
        break;
    case 1:
        month = "Feb";
        break;
    case 2:
        month = "Mar";
        break;
    case 3:
        month = "Apr";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "Jun";
        break;
    case 6:
        month = "Jul";
        break;
    case 7:
        month = "Aug";
        break;
    case 8:
        month = "Sep";
        break;
    case 9:
        month = "Oct";
        break;
    case 10:
        month = "Nov";
        break;
    case 11:
        month = "Dec";
        break;
    }

    sprintf(dest, "%.3s, %02d %.3s %04d %02d:%02d:%02d GMT", weekday,
            current_time.tm_mday, month, current_time.tm_year + 1900,
            current_time.tm_hour, current_time.tm_min, current_time.tm_sec);
    dest[30] = 0;
}

struct Request parse_request(char *packet)
{
    // ! DEBUG
    // printf("Parsing packet:\n--------------------------------\n%s--------------------------------\n", packet);

    char *method = strtok(packet, " "),
         *endpoint = strtok(NULL, " "),
         *http_version = strtok(NULL, "\n");
    http_version[strlen(http_version) - 1] = 0;
    return (struct Request){method, endpoint, http_version};
}