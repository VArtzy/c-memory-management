#include <assert.h>
#include <stdlib.h>

#include "snekobject.h"

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

// don't touch below this line

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

void test_positive() {
    snek_object_t *obj = new_snek_float(42);
    assert(obj->data.v_float == 42);

    free(obj);
}

void test_zero() {
    snek_object_t *obj = new_snek_float(0.0);

    assert(obj->kind == FLOAT);
    assert(obj->data.v_float == 0.0);

    free(obj);
}

void test_negative() {
    snek_object_t *obj = new_snek_float(-5.0);

    assert(obj->kind == FLOAT);
    assert(obj->data.v_float == -5.0);

    free(obj);
}

int main() {
    test_positive();
    test_zero();
    test_negative();
    return 0;
}
