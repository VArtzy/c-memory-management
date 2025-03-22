#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "exercise.h"

char *get_full_greeting(char *greeting, char *name, int size) {
  char *full_greeting = (char*)malloc(size * sizeof(char));
  if (full_greeting == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
  }
  snprintf(full_greeting, size, "%s %s", greeting, name);
  return full_greeting;
}

// Helper function to check if a pointer is on the stack
bool is_on_stack(void *ptr) {
    void *stack_top = __builtin_frame_address(0);
    uintptr_t stack_top_addr = (uintptr_t)stack_top;
    uintptr_t ptr_addr = (uintptr_t)ptr;

    // Check within a threshold in both directions (e.g., 1MB)
    uintptr_t threshold = 1024 * 1024; // 1MB threshold

    return ptr_addr >= (stack_top_addr - threshold) && ptr_addr <= (stack_top_addr + threshold);
}

void test_basic_greeting() {
    char *result = get_full_greeting("Hello", "Alice", 20);
    assert(strcmp(result, "Hello Alice") == 0);
    assert(!is_on_stack(result));
    free(result);
}

void test_short_buffer() {
    char *result = get_full_greeting("Hey", "Bob", 4);
    assert(strcmp(result, "Hey") == 0);
    assert(!is_on_stack(result));
    free(result);
}

int main() {
    test_basic_greeting();
    test_short_buffer();
    return 0;
}
