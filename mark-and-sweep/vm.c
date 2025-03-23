#include <assert.h>
#include <stdlib.h>
#include "vm.h"

vm_t *vm_new() {
    vm_t *vm = malloc(sizeof(vm_t));
    vm->frames = stack_new(8);
    vm->objects = stack_new(8);
    return vm;
}

void vm_free(vm_t *vm) {
    stack_free(vm->frames);
    stack_free(vm->objects);
    free(vm);
}

void test_vm_new() {
    vm_t *vm = vm_new();
    assert(vm->frames->capacity == 8);
    assert(vm->objects->capacity == 8);
    vm_free(vm);
}

void test_vm_new_free() {
    vm_t *vm = vm_new();
    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

int main() {
    test_vm_new();
    test_vm_new_free();
    return 0;
}
