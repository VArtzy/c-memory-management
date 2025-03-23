#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "snekobject.h"

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
    if (snek_obj == NULL || value == NULL) { return false; }
    if (snek_obj->kind != ARRAY) { return false; }
    if (index >= snek_obj->data.v_array.size) { return false; }

    snek_obj->data.v_array.elements[index] = value;
    return true;
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
    if (snek_obj == NULL) { return NULL; }
    if (snek_obj->kind != ARRAY) { return NULL; }
    if (index >= snek_obj->data.v_array.size) { return NULL; }

    return snek_obj->data.v_array.elements[index];
}

// don't touch below this line

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

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

void test_array() {
    snek_object_t *obj = new_snek_array(2);

    snek_object_t *first = new_snek_string("First");
    snek_object_t *second = new_snek_integer(3);

    assert(snek_array_set(obj, 0, first));
    assert(snek_array_set(obj, 1, second));

    snek_object_t *retrieved_first = snek_array_get(obj, 0);
    assert(retrieved_first != NULL);
    assert(retrieved_first->kind == STRING);
    assert(retrieved_first == first);

    snek_object_t *retrieved_second = snek_array_get(obj, 1);
    assert(retrieved_second != NULL);
    assert(retrieved_second->kind == INTEGER);
    assert(retrieved_second == second);

    free(first->data.v_string);
    free(first);
    free(second);
    free(obj->data.v_array.elements);
    free(obj);
}

void test_set_outside_bounds() {
    snek_object_t *obj = new_snek_array(2);

    snek_object_t *outside = new_snek_string("First");

    assert(snek_array_set(obj, 1, outside));
    assert(!snek_array_set(obj, 100, outside));

    free(outside->data.v_string);
    free(outside);
    free(obj->data.v_array.elements);
    free(obj);
}

void test_get_outside_bounds() {
    snek_object_t *obj = new_snek_array(1);
    snek_object_t *first = new_snek_string("First");
    assert(snek_array_set(obj, 0, first));

    assert(snek_array_get(obj, 1) == NULL);

    free(first->data.v_string);
    free(first);
    free(obj->data.v_array.elements);
    free(obj);
}

int main() {
    test_array();
    test_set_outside_bounds();
    test_get_outside_bounds();
    return 0;
}
