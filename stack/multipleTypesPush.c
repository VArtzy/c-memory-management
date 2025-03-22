#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "snekstack.h"
#include "exercise.h"

void stack_push_multiple_types(stack_t *s) {
    float *phi = malloc(sizeof(float));
    *phi = 3.14;
    stack_push(s, phi); // push a float value

    char *text = "Sneklang is blazingly slow!";
    char *str = malloc(sizeof(char) * strlen(text));
    str = text;
    stack_push(s, str); // push a char* (string)
    // This stack even accept different datatypes between element, with great power comes great responsiblity
    // in statically typed languages, it's often better to enforce type homogeneity ensure type safety and clarity.
}

void scary_double_push(stack_t *s) {
    stack_push(s, (void *)1337); // push an int value cast to void *
    int *mem = malloc(sizeof(int));
    *mem = 1024;
    stack_push(s, mem); // push a pointer to a value
    // This dangerious because we let every datatype pushed onto the stack, make it heterogeneous (usually bad idea)
}

void stack_free(stack_t *stack) {
    if (stack->data == NULL) {
        return;
    } else {
        free(stack->data);
        free(stack);
    }
}

void *stack_pop(stack_t *stack) {
    if (stack->data == NULL) {
        return NULL;
    }

    void *data = stack->data[stack->count];
    stack->count--;
    return data;
}

void stack_push(stack_t *stack, void *obj) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        void *data = realloc(stack->data, stack->capacity * sizeof(void *));
        if (data == NULL) {
            stack->capacity /= 2;
            return;
        }
        stack->data = data;
    }

    stack->data[stack->count] = obj;
    stack->count++;
}

stack_t *stack_new(size_t capacity) {
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capacity;
    stack->data = malloc(capacity * sizeof(void *));

    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

void multiple_types_stack() {
    stack_t *s = stack_new(4);
    assert(s != NULL);

    stack_push_multiple_types(s);
    assert(s->count == 2);

    float *f = s->data[0];
    assert(*f == 3.14f);

    char *string = s->data[1];
    assert(strcmp(string, "Sneklang is blazingly slow!") == 0);

    free(f);
    free(string);
    stack_free(s);
}

int main() {
    multiple_types_stack();
    return 0;
}
