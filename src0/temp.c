#include <stdio.h>

#include "server/http.h"

int main()
{
    printf("content type of temp.tiff is %s\n", get_content_type("temp.tiff"));
    printf("content type of temp.json is %s\n", get_content_type("temp.json"));
    printf("content type of temp.html is %s\n", get_content_type("temp.html"));
    printf("content type of temp.log.txt is %s\n", get_content_type("temp.log.txt"));
}