#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
  if (snek_obj == NULL || value == NULL) {
    return false;
  }
  if (snek_obj->kind != ARRAY) {
    return false;
  }
  if (index >= snek_obj->data.v_array.size) {
    return false;
  }
  refcount_inc(value);
  if (snek_obj->data.v_array.elements[index] != NULL) {
      refcount_dec(snek_obj->data.v_array.elements[index]);
  }
  snek_obj->data.v_array.elements[index] = value;
  return true;
}

void refcount_free(snek_object_t *obj) {
  switch (obj->kind) {
  case INTEGER:
  case FLOAT:
    break;
  case STRING:
    free(obj->data.v_string);
    break;
  case VECTOR3: {
    snek_vector_t vec = obj->data.v_vector3;
    refcount_dec(vec.x);
    refcount_dec(vec.y);
    refcount_dec(vec.z);
    break;
  }
  case ARRAY:
  for (int i = 0; i < obj->data.v_array.size; i++) {
      refcount_dec(obj->data.v_array.elements[i]);
  }
  free(obj->data.v_array.elements);
  break;
  default:
    assert(false);
  }
  free(obj);
}

// don't touch below this line

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
  if (snek_obj == NULL) {
    return NULL;
  }

  if (snek_obj->kind != ARRAY) {
    return NULL;
  }

  if (index >= snek_obj->data.v_array.size) {
    return NULL;
  }

  return snek_obj->data.v_array.elements[index];
}

void refcount_inc(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount++;
  return;
}

void refcount_dec(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }
  obj->refcount--;
  if (obj->refcount == 0) {
    return refcount_free(obj);
  }
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
  refcount_inc(x);
  refcount_inc(y);
  refcount_inc(z);
  return obj;
}

void test_array_set() {
    snek_object_t *foo = new_snek_integer(1);

    snek_object_t *array = new_snek_array(1);
    snek_array_set(array, 0, foo);
    assert(foo->refcount == 2);

    // Assuming `boot_is_freed` is implemented elsewhere
    // assert(!boot_is_freed(foo));

    refcount_dec(foo);
    refcount_dec(array);
    // assert(boot_all_freed());
}

void test_array_free() {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *array = new_snek_array(2);
    snek_array_set(array, 0, foo);
    snek_array_set(array, 1, bar);
    assert(foo->refcount == 2);
    assert(bar->refcount == 2);
    assert(baz->refcount == 1);

    refcount_dec(foo);
    // assert(!boot_is_freed(foo));

    snek_array_set(array, 0, baz);
    // assert(boot_is_freed(foo));

    refcount_dec(bar);
    refcount_dec(baz);
    refcount_dec(array);
    // assert(boot_all_freed());
}

void test_vector3_refcounting() {
    snek_object_t *foo = new_snek_integer(1);
    snek_object_t *bar = new_snek_integer(2);
    snek_object_t *baz = new_snek_integer(3);

    snek_object_t *vec = new_snek_vector3(foo, bar, baz);
    assert(foo->refcount == 2);
    assert(bar->refcount == 2);
    assert(baz->refcount == 2);

    refcount_dec(foo);
    // assert(!boot_is_freed(foo));

    refcount_dec(vec);
    // assert(boot_is_freed(foo));

    // assert(!boot_is_freed(bar));
    // assert(!boot_is_freed(baz));

    refcount_dec(bar);
    refcount_dec(baz);

    // assert(boot_all_freed());
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

    // assert(!boot_is_freed(obj));

    free(obj);
}

void test_refcount_free_is_called() {
    snek_object_t *obj = new_snek_float(4.20);

    refcount_inc(obj);
    assert(obj->refcount == 2);

    refcount_dec(obj);
    assert(obj->refcount == 1);

    refcount_dec(obj);
    // assert(boot_is_freed(obj));
    // assert(boot_all_freed());
}

void test_allocated_string_is_freed() {
    snek_object_t *obj = new_snek_string("Hello @wagslane!");

    refcount_inc(obj);
    assert(obj->refcount == 2);

    refcount_dec(obj);
    assert(obj->refcount == 1);
    assert(strcmp(obj->data.v_string, "Hello @wagslane!") == 0);

    refcount_dec(obj);
    // assert(boot_is_freed(obj));
    // assert(boot_all_freed());
}

int main() {
    test_array_set();
    test_array_free();
    test_vector3_refcounting();
    test_int_has_refcount();
    test_inc_refcount();
    test_dec_refcount();
    test_refcount_free_is_called();
    test_allocated_string_is_freed();
    return 0;
}
