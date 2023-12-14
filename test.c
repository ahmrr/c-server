#include <time.h>
#include <stdio.h>

#include "include/http.h"
// #include "include/util.h"

int main()
{
    // ? -------------------------------------------------------------------- //

    // printf("content type of temp.tiff is %s\n", get_content_type("temp.tiff"));
    // printf("content type of temp.json is %s\n", get_content_type("temp.json"));
    // printf("content type of temp.html is %s\n", get_content_type("temp.html"));
    // printf("content type of temp.log.txt is %s\n", get_content_type("temp.log.txt"));

    // printf("status of 200 is %s\n", make_status(200));
    // printf("status of 404 is %s\n", make_status(404));
    // printf("status of 418 is %s\n", make_status(418));
    // printf("status of 501 is %s\n", make_status(501));

    // int x = 5;
    // printf("the value of x is\t%d\n", x);
    // printf("the value of x += 5 is\t%d\n", x += 5);
    // printf("the value of x after is\t%d\n", x);

    // unsigned char *bytes = NULL;
    // size_t bytes_read = read_file("index.html", &bytes);
    // printf("read a total of %lu bytes from test.txt\n", bytes_read);
    // free(bytes);

    // ? -------------------------------------------------------------------- //

    // size_t n1 = 1UL;
    // size_t n2 = -1UL;

    // clock_t begin = clock();

    // int n1_digits = digits(n1);

    // clock_t end = clock();

    // double n1_time = (double)(end - begin) / CLOCKS_PER_SEC;

    // begin = clock();

    // int n2_digits = digits(n2);

    // end = clock();

    // double n2_time = (double)(end - begin) / CLOCKS_PER_SEC;

    // printf("n1_time: %lf\nn1_digits: %d\n\nn2_time: %lf\nn2_digits: %d\n", n1_time, n1_digits, n2_time, n2_digits);

    // ? -------------------------------------------------------------------- //

    // printf("size of file \"index.html\" is %lu\n", file_size("index.html"));

    // ? -------------------------------------------------------------------- //

    char packet[] = "GET /http/files/index.html\n";

    struct Request request = parse_request(packet);
    printf("request method is %s\nrequest endpoint is %s\n", request.method, request.endpoint);
}