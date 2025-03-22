#include <assert.h>
#include "exercise.h"

void swap_ints(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void test_swap_ints() {
    int a = 5;
    int b = 6;

    swap_ints(&a, &b);

    assert(a == 6);
    assert(b == 5);
}

void test_swap_ints_same() {
    int a = 5;

    swap_ints(&a, &a);

    assert(a == 5);
}

int main() {
    test_swap_ints();
    test_swap_ints_same();
    return 0;
}
