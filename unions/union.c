#include <stdio.h>
#include "exercise.h"
#include <assert.h>
#include <string.h>

void format_object(snek_object_t obj, char *buffer) {
    switch (obj.kind) {
        case INTEGER: 
            sprintf(buffer, "int:%d", obj.data.v_int);
            break;
        case STRING:
            sprintf(buffer, "string:%s", obj.data.v_string);
            break;
    }
}

// don't touch below this line'

snek_object_t new_integer(int i) {
  return (snek_object_t){
    .kind = INTEGER,
    .data = {.v_int = i}
  };
}

snek_object_t new_string(char *str) {
  // NOTE: We will learn how to copy this data later.
  return (snek_object_t){
    .kind = STRING,
    .data = {.v_string = str}
  };
}

void test_formats_int1() {
    char buffer[100];
    snek_object_t i = new_integer(5);
    format_object(i, buffer);
    assert(strcmp(buffer, "int:5") == 0);
}

void test_formats_string1() {
    char buffer[100];
    snek_object_t s = new_string("Hello!");
    format_object(s, buffer);
    assert(strcmp(buffer, "string:Hello!") == 0);
}

void test_formats_int2() {
    char buffer[100];
    snek_object_t i = new_integer(2014);
    format_object(i, buffer);
    assert(strcmp(buffer, "int:2014") == 0);
}

void test_formats_string2() {
    char buffer[100];
    snek_object_t s = new_string("nvim btw");
    format_object(s, buffer);
    assert(strcmp(buffer, "string:nvim btw") == 0);
}

int main() {
    test_formats_int1();
    test_formats_string1();
    test_formats_int2();
    test_formats_string2();
    return 0;
}
