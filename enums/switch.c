#include <assert.h>
#include <string.h>
#include "http.h"

char *http_to_str(HttpErrorCode code) {
    switch (code) {
        case HTTP_BAD_REQUEST:
            return "400 Bad Request";
            break;
        case HTTP_UNAUTHORIZED:
            return "401 Unauthorized";
            break;
        case HTTP_NOT_FOUND:
            return "404 Not Found";
            break;
        case HTTP_TEAPOT:
            return "418 I AM A TEAPOT!";
            break;
        case HTTP_INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
            break;
        default:
            return "Unknown HTTP status code";
            break;
    }
}

void test_switch_enum() {
    assert(strcmp(http_to_str(HTTP_BAD_REQUEST), "400 Bad Request") == 0);
    assert(strcmp(http_to_str(HTTP_UNAUTHORIZED), "401 Unauthorized") == 0);
    assert(strcmp(http_to_str(HTTP_NOT_FOUND), "404 Not Found") == 0);
    assert(strcmp(http_to_str(HTTP_TEAPOT), "418 I AM A TEAPOT!") == 0);
    assert(strcmp(http_to_str(HTTP_INTERNAL_SERVER_ERROR), "500 Internal Server Error") == 0);
}

void test_switch_enum_default() {
    assert(strcmp(http_to_str((HttpErrorCode)999), "Unknown HTTP status code") == 0);
}

int main() {
    test_switch_enum();
    test_switch_enum_default();
    return 0;
}
