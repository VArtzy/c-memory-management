#include <assert.h>
#include <stdlib.h>
#include "snekobject.h"

void test_integer_constant() {
    assert(INTEGER == 0);
}

void test_integer_obj() {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    obj->kind = INTEGER;
    obj->data.v_int = 0;
    assert(obj->kind == INTEGER);
    assert(obj->data.v_int == 0);

    free(obj);
}

int main() {
    test_integer_constant();
    test_integer_obj();
    return 0;
}
