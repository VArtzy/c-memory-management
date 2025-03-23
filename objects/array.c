#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "snekobject.h"

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **array = calloc(sizeof(void *), size);
  if (array == NULL) {
      free(obj);
      return NULL;
  }

  obj->kind = ARRAY;
  snek_array_t arr = {
      .size = size,
      .elements = array
  };
  obj->data.v_array = arr;
  return obj;
}

// don't touch below this line

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

void test_create_empty_array() {
    snek_object_t *obj = new_snek_array(2);

    assert(obj->kind == ARRAY);
    assert(obj->data.v_array.size == 2);

    free(obj->data.v_array.elements);
    free(obj);
}

void test_used_calloc() {
    snek_object_t *obj = new_snek_array(2);

    assert(obj->data.v_array.elements[0] == NULL);
    assert(obj->data.v_array.elements[1] == NULL);

    free(obj->data.v_array.elements);
    free(obj);
}

int main() {
    test_create_empty_array();
    test_used_calloc();
    return 0;
}
