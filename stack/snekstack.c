#include <stdlib.h>
#include <assert.h>
#include "snekstack.h"

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

void create_stack_small() {
    stack_t *s = stack_new(3);
    assert(s->capacity == 3);
    assert(s->count == 0);
    assert(s->data != NULL);

    free(s->data);
    free(s);
}

void create_stack_large() {
    stack_t *s = stack_new(100);
    assert(s->capacity == 100);
    assert(s->count == 0);
    assert(s->data != NULL);

    free(s->data);
    free(s);
}

int main() {
    create_stack_small();
    create_stack_large();
    return 0;
}
