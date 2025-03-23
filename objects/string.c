#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "snekobject.h"

snek_object_t *new_snek_string(char *value) { 
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value) + 1;
  char *string = malloc(sizeof(char *) * len);
  if (string == NULL) {
      free(obj);
      return NULL;
  }

  strcpy(string, value);
  obj->kind = STRING;
  obj->data.v_string = string;
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

void test_str_copied() {
    char *input = "Hello, World!";
    snek_object_t *obj = new_snek_string(input);

    assert(obj->kind == STRING);

    // Ensure the string is copied, not just referenced
    assert(obj->data.v_string != input);
    assert(strcmp(obj->data.v_string, input) == 0);

    // Free the string and the object
    free(obj->data.v_string);
    free(obj);
}

int main() {
    test_str_copied();
    return 0;
}
