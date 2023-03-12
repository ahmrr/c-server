#include <stdio.h>

#include "../include/http.h"

int main()
{
    printf("content type of temp.tiff is %s\n", get_content_type("temp.tiff"));
    printf("content type of temp.json is %s\n", get_content_type("temp.json"));
    printf("content type of temp.html is %s\n", get_content_type("temp.html"));
    printf("content type of temp.log.txt is %s\n", get_content_type("temp.log.txt"));

    printf("status of 200 is %s\n", make_status(200));
    printf("status of 404 is %s\n", make_status(404));
    printf("status of 418 is %s\n", make_status(418));
    printf("status of 501 is %s\n", make_status(501));
}