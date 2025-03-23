#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
    if (x == NULL || y == NULL || z == NULL) { return NULL; }

    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) { return NULL; }

    obj->kind = VECTOR3;
    snek_vector_t vector3 = {
        .x = x,
        .y = y,
        .z = z
    };
    obj->data.v_vector3 = vector3;
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

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}

void test_returns_null() {
    snek_object_t *vec = new_snek_vector3(NULL, NULL, NULL);
    assert(vec == NULL);
}

void test_vec_multiple_objects() {
    snek_object_t *x = new_snek_integer(1);
    snek_object_t *y = new_snek_integer(2);
    snek_object_t *z = new_snek_integer(3);
    snek_object_t *vec = new_snek_vector3(x, y, z);

    assert(vec != NULL);

    assert(vec->data.v_vector3.x == x);
    assert(vec->data.v_vector3.y == y);
    assert(vec->data.v_vector3.z == z);

    assert(vec->data.v_vector3.x->data.v_int == 1);
    assert(vec->data.v_vector3.y->data.v_int == 2);
    assert(vec->data.v_vector3.z->data.v_int == 3);

    free(x);
    free(y);
    free(z);
    free(vec);
}

void test_vec_same_object() {
    snek_object_t *i = new_snek_integer(1);
    snek_object_t *vec = new_snek_vector3(i, i, i);

    assert(vec != NULL);

    assert(vec->data.v_vector3.x == i);
    assert(vec->data.v_vector3.y == i);
    assert(vec->data.v_vector3.z == i);

    assert(vec->data.v_vector3.x->data.v_int == 1);
    assert(vec->data.v_vector3.y->data.v_int == 1);
    assert(vec->data.v_vector3.z->data.v_int == 1);

    i->data.v_int = 2;

    assert(vec->data.v_vector3.x->data.v_int == 2);
    assert(vec->data.v_vector3.y->data.v_int == 2);
    assert(vec->data.v_vector3.z->data.v_int == 2);

    free(i);
    free(vec);
}

int main() {
    test_returns_null();
    test_vec_multiple_objects();
    test_vec_same_object();
    return 0;
}
