#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

void refcount_dec(snek_object_t *obj) {
    if (obj == NULL) { return; }
    obj->refcount--;
    if (obj->refcount == 0) {
        refcount_free(obj);
    }
}

void refcount_free(snek_object_t *obj) {
    switch (obj->kind) {
        case INTEGER:
            break;
        case FLOAT:
            break;
        case STRING:
            free(obj->data.v_string);
            break;
    }
    free(obj);
}

// don't touch below this line

void refcount_inc(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount++;
  return;
}

snek_object_t *_new_snek_object() {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->refcount = 1;

  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
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

  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = _new_snek_object();
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

void test_int_has_refcount() {
    snek_object_t *obj = new_snek_integer(10);
    assert(obj->refcount == 1);

    free(obj);
}

void test_inc_refcount() {
    snek_object_t *obj = new_snek_float(4.20);
    assert(obj->refcount == 1);

    refcount_inc(obj);
    assert(obj->refcount == 2);

    free(obj);
}

void test_dec_refcount() {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert(obj->refcount == 2);

    refcount_dec(obj);
    assert(obj->refcount == 1);

    free(obj);
}

void test_refcount_free_is_called() {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert(obj->refcount == 2);

    refcount_dec(obj);
    assert(obj->refcount == 1);

    refcount_dec(obj);
    // Assuming `boot_is_freed` and `boot_all_freed` are implemented elsewhere
}

void test_allocated_string_is_freed() {
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    assert(obj->refcount == 2);

    refcount_dec(obj);
    assert(obj->refcount == 1);
    assert(strcmp(obj->data.v_string, "Hello @wagslane!") == 0);

    refcount_dec(obj);
    // Assuming `boot_is_freed` and `boot_all_freed` are implemented elsewhere
}

int main() {
    test_int_has_refcount();
    test_inc_refcount();
    test_dec_refcount();
    test_refcount_free_is_called();
    test_allocated_string_is_freed();
    return 0;
}
