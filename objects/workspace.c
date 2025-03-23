#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) { return NULL; }

    switch (a->kind) {
        case INTEGER:
            switch (b->kind) {
                case INTEGER:
                    return new_snek_integer(a->data.v_int + b->data.v_int);
                case FLOAT:
                    return new_snek_float((float)a->data.v_int + b->data.v_float);
                default:
                    return NULL;
            }
        case FLOAT:
            switch (b->kind) {
                case INTEGER:
                    return new_snek_float(a->data.v_float + (float)b->data.v_int);
                case FLOAT:
                    return new_snek_float(a->data.v_float + b->data.v_float);
                default:
                    return NULL;
            }
        case STRING:
            if (b->kind != STRING) { return NULL; }

            int len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
            char *temp = calloc(len, sizeof(char *));
            strcat(temp, a->data.v_string);
            strcat(temp, b->data.v_string);
            snek_object_t *str = new_snek_string(temp);
            free(temp);
            return str;
        case VECTOR3:
            if (b->kind != VECTOR3) { return NULL; }

            snek_object_t *vec = new_snek_vector3(
                snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
                snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
            );
            return vec;
        case ARRAY:
            if (b->kind != ARRAY) { return NULL; }

            size_t size_a = a->data.v_array.size;
            size_t size_b = b->data.v_array.size;
            size_t size = size_a + size_b;
            snek_object_t *arr = new_snek_array(size);
            for (int i = 0; i < size_a; i++) {
                snek_array_set(arr, i, snek_array_get(a, i));
            }
            for (int i = 0; i < size_b; i++) {
                snek_array_set(arr, i + size_a, snek_array_get(b, i));
            }
            return arr;
        default:
            return NULL;

    }
}

// don't touch below this line

int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOAT:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case VECTOR3:
    return 3;
  case ARRAY:
    return obj->data.v_array.size;
  default:
    return -1;
  }
}

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

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
  if (array == NULL || value == NULL) {
    return false;
  }

  if (array->kind != ARRAY) {
    return false;
  }

  if (index >= array->data.v_array.size) {
    return false;
  }

  // Set the value directly now (already checked size constraint)
  array->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
  if (array == NULL) {
    return NULL;
  }

  if (array->kind != ARRAY) {
    return NULL;
  }

  if (index >= array->data.v_array.size) {
    return NULL;
  }

  // Set the value directly now (already checked size constraint)
  return array->data.v_array.elements[index];
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

void test_integer_add() {
    snek_object_t *one = new_snek_integer(1);
    snek_object_t *three = new_snek_integer(3);
    snek_object_t *four = snek_add(one, three);

    assert(four != NULL);
    assert(four->kind == INTEGER);
    assert(four->data.v_int == 4);

    free(one);
    free(three);
    free(four);
}

void test_float_add() {
    snek_object_t *one = new_snek_float(1.5);
    snek_object_t *three = new_snek_float(3.5);
    snek_object_t *five = snek_add(one, three);

    assert(five != NULL);
    assert(five->kind == FLOAT);
    assert(five->data.v_float == 1.5 + 3.5);

    free(one);
    free(three);
    free(five);
}

void test_string_add() {
    snek_object_t *hello = new_snek_string("hello");
    snek_object_t *world = new_snek_string(", world");
    snek_object_t *greeting = snek_add(hello, world);

    assert(greeting != NULL);
    assert(greeting->kind == STRING);
    assert(strcmp(greeting->data.v_string, "hello, world") == 0);

    free(hello->data.v_string);
    free(hello);
    free(world->data.v_string);
    free(world);
    free(greeting->data.v_string);
    free(greeting);
}

void test_string_add_self() {
    snek_object_t *repeated = new_snek_string("(repeated)");
    snek_object_t *result = snek_add(repeated, repeated);

    assert(result != NULL);
    assert(result->kind == STRING);
    assert(strcmp(result->data.v_string, "(repeated)(repeated)") == 0);

    free(repeated->data.v_string);
    free(repeated);
    free(result->data.v_string);
    free(result);
}

void test_vector3_add() {
    snek_object_t *one = new_snek_float(1.0);
    snek_object_t *two = new_snek_float(2.0);
    snek_object_t *three = new_snek_float(3.0);
    snek_object_t *four = new_snek_float(4.0);
    snek_object_t *five = new_snek_float(5.0);
    snek_object_t *six = new_snek_float(6.0);

    snek_object_t *v1 = new_snek_vector3(one, two, three);
    snek_object_t *v2 = new_snek_vector3(four, five, six);
    snek_object_t *result = snek_add(v1, v2);

    assert(result != NULL);
    assert(result->kind == VECTOR3);

    assert(result->data.v_vector3.x->data.v_float == 5.0);
    assert(result->data.v_vector3.y->data.v_float == 7.0);
    assert(result->data.v_vector3.z->data.v_float == 9.0);

    free(v1->data.v_vector3.x);
    free(v1->data.v_vector3.y);
    free(v1->data.v_vector3.z);
    free(v1);

    free(v2->data.v_vector3.x);
    free(v2->data.v_vector3.y);
    free(v2->data.v_vector3.z);
    free(v2);

    free(result->data.v_vector3.x);
    free(result->data.v_vector3.y);
    free(result->data.v_vector3.z);
    free(result);
}

void test_array_add() {
    snek_object_t *one = new_snek_integer(1);
    snek_object_t *ones = new_snek_array(2);
    assert(snek_array_set(ones, 0, one));
    assert(snek_array_set(ones, 1, one));

    snek_object_t *hi = new_snek_string("hi");
    snek_object_t *hellos = new_snek_array(3);
    assert(snek_array_set(hellos, 0, hi));
    assert(snek_array_set(hellos, 1, hi));
    assert(snek_array_set(hellos, 2, hi));

    snek_object_t *result = snek_add(ones, hellos);

    assert(result != NULL);
    assert(result->kind == ARRAY);

    snek_object_t *first = snek_array_get(result, 0);
    assert(first != NULL);
    assert(first->data.v_int == 1);

    snek_object_t *third = snek_array_get(result, 2);
    assert(third != NULL);
    assert(strcmp(third->data.v_string, "hi") == 0);

    free(one);
    free(ones->data.v_array.elements);
    free(ones);

    free(hi->data.v_string);
    free(hi);
    free(hellos->data.v_array.elements);
    free(hellos);
    free(result->data.v_array.elements);
    free(result);
}

int main() {
    test_integer_add();
    test_float_add();
    test_string_add();
    test_string_add_self();
    test_vector3_add();
    test_array_add();
    return 0;
}
