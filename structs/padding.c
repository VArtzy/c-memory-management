#include <stdio.h>
#include <assert.h>
#include "exercise.h"

void test_optimal_size() {
    printf("%zu\n", sizeof(sneklang_var_t));
    assert(sizeof(sneklang_var_t) == 24);
}

int main() {
    test_optimal_size();
    return 0;
}
