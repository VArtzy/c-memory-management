#include <stdio.h>
#include <assert.h>
#include "exercise.h"

void snek_zero_out(void *ptr, snek_object_kind_t kind){
    if (kind == INTEGER) {
        snek_int_t *number = (snek_int_t*)ptr;
        number->value = 0;
    } else if (kind == FLOAT) {
        snek_float_t *number = (snek_float_t*)ptr;
        number->value = 0.0;
    } else if (kind == BOOL) {
        snek_bool_t *number = (snek_bool_t*)ptr;
        number->value = 0;
    } else {
        exit(1);
    }
}

void test_zero_out_integer() {
    snek_int_t integer;
    integer.value = 42;
    snek_zero_out(&integer, INTEGER);
    assert(integer.value == 0);
}

void test_zero_out_float() {
    snek_float_t float_num;
    float_num.value = 3.14;
    snek_zero_out(&float_num, FLOAT);
    assert(float_num.value == 0.0);
}

void test_zero_out_bool() {
    snek_bool_t boolean;
    boolean.value = 1;
    snek_zero_out(&boolean, BOOL);
    assert(boolean.value == 0);
}

void test_zero_out_nonzero_values() {
    snek_int_t integer;
    snek_float_t float_num;
    snek_bool_t boolean;

    integer.value = -100;
    float_num.value = -99.99;
    boolean.value = 255;

    snek_zero_out(&integer, INTEGER);
    snek_zero_out(&float_num, FLOAT);
    snek_zero_out(&boolean, BOOL);

    assert(integer.value == 0);
    assert(float_num.value == 0.0);
    assert(boolean.value == 0);
}

int main() {
    test_zero_out_integer();
    test_zero_out_float();
    test_zero_out_bool();
    test_zero_out_nonzero_values();
    return 0;
}
