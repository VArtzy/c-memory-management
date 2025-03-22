#include <assert.h>
#include "stdlib.h"
#include "exercise.h"

void allocate_int(int **pointer_pointer, int value) {
    int *ptr = malloc(sizeof(int));
    *pointer_pointer = ptr;
    **pointer_pointer = value;
}

void test_allocate() {
    int *pointer = NULL;
    allocate_int(&pointer, 10);

    assert(pointer != NULL);
    assert(*pointer == 10);

    free(pointer);
}

void test_does_not_overwrite() {
    int value = 5;
    int *pointer = &value;

    allocate_int(&pointer, 20);

    assert(value == 5);
    assert(pointer != NULL);
    assert(*pointer == 20);

    free(pointer);
}

int main() {
    test_allocate();
    test_does_not_overwrite();
    return 0;
}
