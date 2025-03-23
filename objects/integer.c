#include <assert.h>
#include <stdlib.h>

#include "snekobject.h"

snek_object_t *new_snek_integer(int value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = INTEGER;
    obj->data.v_int = value;

    return obj;
}

void test_positive() {
    snek_object_t *int_object = new_snek_integer(42);
    assert(int_object->data.v_int == 42);

    free(int_object);
}

void test_zero() {
    snek_object_t *int_object = new_snek_integer(0);

    assert(int_object->kind == INTEGER);
    assert(int_object->data.v_int == 0);

    free(int_object);
}

void test_negative() {
    snek_object_t *int_object = new_snek_integer(-5);

    assert(int_object->kind == INTEGER);
    assert(int_object->data.v_int == -5);

    free(int_object);
}

int main() {
    test_positive();
    test_zero();
    test_negative();
    return 0;
}
