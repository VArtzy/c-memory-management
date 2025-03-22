#include <assert.h>
#include <string.h>
#include "exercise.h"

void concat_strings(char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0') {
        i++;
    }

    int j = 0;
    while (str2[j] != '\0') {
        str1[i + j] = str2[j];
        j++;
    }

    str1[i + j] = '\0';
}

void test_concat_empty_strings() {
    char str1[100] = "";
    const char *str2 = "";
    concat_strings(str1, str2);
    assert(strcmp(str1, "") == 0);
}

void test_concat_empty_to_nonempty() {
    char str1[100] = "Hello";
    const char *str2 = "";
    concat_strings(str1, str2);
    assert(strcmp(str1, "Hello") == 0);
}

void test_concat_small_strings() {
    char str1[100] = "Hello ";
    const char *str2 = "World";
    concat_strings(str1, str2);
    assert(strcmp(str1, "Hello World") == 0);
}

void test_concat_long_strings() {
    char str1[200] = "This is a longer string that ";
    const char *str2 = "will be concatenated with another long string.";
    concat_strings(str1, str2);
    assert(strcmp(str1, "This is a longer string that will be concatenated with another long string.") == 0);
}

void test_concat_nonempty_to_empty() {
    char str1[100] = "";
    const char *str2 = "Hello";
    concat_strings(str1, str2);
    assert(strcmp(str1, "Hello") == 0);
}

int main() {
    test_concat_empty_strings();
    test_concat_empty_to_nonempty();
    test_concat_small_strings();
    test_concat_long_strings();
    test_concat_nonempty_to_empty();
    return 0;
}
