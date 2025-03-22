#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "exercise.h"

int smart_append(TextBuffer* dest, const char* src) {
    if (dest == NULL || src == NULL) return 1;

    const int MAX_BUFFER = 64;
    int len = strlen(src);
    int rem = MAX_BUFFER - dest->length - 1;
    
    if (len > rem) {
        strncat(dest->buffer, src, rem);
        dest->length = MAX_BUFFER - 1;
        return 1;
    } else {
        strcat(dest->buffer, src);
        dest->length += len;
        return 0;
    }
}

void test_return_1_for_null_value() {
    TextBuffer dest;
    const char* src = NULL;
    int result = smart_append(&dest, src);
    assert(result == 1);
}

void test_smart_append_empty_buffer() {
    TextBuffer dest;
    strcpy(dest.buffer, "");
    dest.length = 0;
    const char* src = "Hello";
    int result = smart_append(&dest, src);
    assert(result == 0);
    assert(strcmp(dest.buffer, "Hello") == 0);
    assert(dest.length == 5);
}

void test_smart_append_full_buffer() {
    TextBuffer dest;
    strcpy(dest.buffer, "This is a very long string that will fill up the entire buffer.");
    dest.length = 63;
    const char* src = " Extra";
    int result = smart_append(&dest, src);
    assert(result == 1);
    assert(strcmp(dest.buffer, "This is a very long string that will fill up the entire buffer.") == 0);
    assert(dest.length == 63);
}

void test_smart_append_overflow() {
    TextBuffer dest;
    strcpy(dest.buffer, "This is a long string");
    dest.length = 21;
    const char* src = " that will fill the whole buffer and leave no space for some of the chars.";
    int result = smart_append(&dest, src);
    assert(result == 1);
    assert(strcmp(dest.buffer, "This is a long string that will fill the whole buffer and leave") == 0);
    assert(dest.length == 63);
}

int main() {
    test_return_1_for_null_value();
    test_smart_append_empty_buffer();
    test_smart_append_full_buffer();
    test_smart_append_overflow();
    return 0;
}
