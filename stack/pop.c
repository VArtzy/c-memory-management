#include "snekstack.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

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

void pop_stack() {
    stack_t *s = stack_new(2);
    assert(s != NULL);

    assert(s->capacity == 2);
    assert(s->count == 0);
    assert(s->data != NULL);

    int one = 1;
    int two = 2;
    int three = 3;

    stack_push(s, &one);
    stack_push(s, &two);

    assert(s->capacity == 2);
    assert(s->count == 2);

    stack_push(s, &three);
    assert(s->capacity == 4);
    assert(s->count == 3);

    int *popped = stack_pop(s);
    assert(*popped == three);

    popped = stack_pop(s);
    assert(*popped == two);

    popped = stack_pop(s);
    assert(*popped == one);

    popped = stack_pop(s);
    assert(popped == NULL);

    free(s->data);
    free(s);
}

void pop_stack_empty() {
    stack_t *s = stack_new(2);
    assert(s != NULL);

    assert(s->capacity == 2);
    assert(s->count == 0);
    assert(s->data != NULL);

    int *popped = stack_pop(s);
    assert(popped == NULL);

    free(s->data);
    free(s);
}

void push_stack() {
    stack_t *s = stack_new(2);
    assert(s != NULL);

    assert(s->capacity == 2);
    assert(s->count == 0);
    assert(s->data != NULL);

    int a = 1;

    stack_push(s, &a);
    stack_push(s, &a);

    assert(s->capacity == 2);
    assert(s->count == 2);

    stack_push(s, &a);
    assert(s->capacity == 4);
    assert(s->count == 3);

    free(s->data);
    free(s);
}

void create_stack() {
    stack_t *s = stack_new(10);
    assert(s->capacity == 10);
    assert(s->count == 0);
    assert(s->data != NULL);

    free(s->data);
    free(s);
}

int main() {
    create_stack();
    push_stack();
    pop_stack();
    pop_stack_empty();
    return 0;
}
