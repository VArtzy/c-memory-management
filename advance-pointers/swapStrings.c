#include <assert.h>
#include <string.h>
#include "exercise.h"

void swap_strings(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void test_swap_str() {
    char *a = "Hello";
    char *b = "Goodbye";

    swap_strings(&a, &b);

    assert(strcmp(a, "Goodbye") == 0);
    assert(strcmp(b, "Hello") == 0);
}

void test_swap_str_long() {
    char *a = "terminal.shop";
    char *b = "ssh";

    swap_strings(&a, &b);

    assert(strcmp(a, "ssh") == 0);
    assert(strcmp(b, "terminal.shop") == 0);
}

int main() {
    test_swap_str();
    test_swap_str_long();
    return 0;
}
