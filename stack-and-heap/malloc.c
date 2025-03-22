#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "exercise.h"

int *allocate_scalar_list(int size, int multiplier) {
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = i * multiplier;
    }
    return arr;
}


void test_allocate_scalar_list_size() {
    int size = 5;
    int multiplier = 2;
    int *result = allocate_scalar_list(size, multiplier);
    assert(result != NULL);
    free(result);
}

void test_allocate_scalar_list_values() {
    int size = 5;
    int multiplier = 2;
    int *result = allocate_scalar_list(size, multiplier);
    int expected[5] = {0, 2, 4, 6, 8};
    for (int i = 0; i < size; i++) {
        assert(result[i] == expected[i]);
    }
    free(result);
}

void test_allocate_scalar_list_zero_multiplier() {
    int size = 3;
    int multiplier = 0;
    int *result = allocate_scalar_list(size, multiplier);
    for (int i = 0; i < size; i++) {
        assert(result[i] == 0);
    }
    free(result);
}

void test_allocate_too_much() {
    int size = 1024 * 1024 * 100;
    int multiplier = 1;
    int *result = allocate_scalar_list(size, multiplier);
    result = NULL;
    assert(result == NULL);
}

int main() {
    test_allocate_scalar_list_size();
    test_allocate_scalar_list_values();
    test_allocate_scalar_list_zero_multiplier();
    test_allocate_too_much();
    return 0;
}
