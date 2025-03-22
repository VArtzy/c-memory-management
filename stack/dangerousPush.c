#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "exercise.h"

void scary_double_push(stack_t *s) {
    stack_push(s, (void *)1337);
    int *mem = malloc(sizeof(int));
    *mem = 1024;
    stack_push(s, mem);
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

void heterogenous_stack() {
    stack_t *s = stack_new(2);
    assert(s != NULL);

    scary_double_push(s);
    assert(s->count == 2);

    int value = (int)s->data[0];
    assert(value == 1337);

    int *pointer = s->data[1];
    assert(*pointer == 1024);

    free(pointer);
    stack_free(s);
}

int main() {
    heterogenous_stack();
    return 0;
}
