#include <assert.h>
#include "exercise.h"

codefile_t change_filetype(codefile_t *f, int new_filetype){
  codefile_t new_f = *f;
  new_f.filetype = new_filetype;
  return new_f;
}

void test_change_filetype_cpp_to_python() {
    codefile_t original;
    original.lines = 100;
    original.filetype = 1;
    codefile_t result = change_filetype(&original, 2);
    assert(result.filetype == 2);
    assert(result.lines == 100);
}

void test_change_filetype_same_type() {
    codefile_t original;
    original.lines = 50;
    original.filetype = 3;
    codefile_t result = change_filetype(&original, 3);
    assert(result.filetype == 3);
    assert(result.lines == 50);
}

void test_change_filetype_java_to_rust() {
    codefile_t original;
    original.lines = 200;
    original.filetype = 4;
    codefile_t result = change_filetype(&original, 5);
    assert(result.filetype == 5);
    assert(result.lines == 200);
}

void test_change_filetype_zero_lines() {
    codefile_t original;
    original.lines = 0;
    original.filetype = 1;
    codefile_t result = change_filetype(&original, 6);
    assert(result.filetype == 6);
    assert(result.lines == 0);
}

void test_change_filetype_no_mutation() {
    codefile_t original;
    original.lines = 150;
    original.filetype = 7;
    codefile_t backup = original;
    codefile_t result = change_filetype(&original, 8);
    assert(result.filetype == 8);
    assert(original.filetype == backup.filetype);
    assert(original.lines == backup.lines);
}

int main() {
    test_change_filetype_cpp_to_python();
    test_change_filetype_same_type();
    test_change_filetype_java_to_rust();
    test_change_filetype_zero_lines();
    test_change_filetype_no_mutation();
    return 0;
}
