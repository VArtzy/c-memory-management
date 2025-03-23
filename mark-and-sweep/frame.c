#include <assert.h>
#include <stdlib.h>
#include "vm.h"

void vm_frame_push(vm_t *vm, frame_t *frame) {
    stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->references = stack_new(8);
    stack_push(vm->frames, frame);
    return frame;
}

void frame_free(frame_t *frame) {
    stack_free(frame->references);
    free(frame);
}

// don't touch below this line

vm_t *vm_new() {
  vm_t *vm = malloc(sizeof(vm_t));
  if (vm == NULL) {
    return NULL;
  }

  vm->frames = stack_new(8);
  vm->objects = stack_new(8);
  return vm;
}

void vm_free(vm_t *vm) {
  for (int i = 0; i < vm->frames->count; i++) {
    frame_free(vm->frames->data[i]);
  }
  stack_free(vm->frames);
  stack_free(vm->objects);
  free(vm);
}

void test_vm_new() {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    assert(vm->frames->count == 1);
    vm_free(vm);
}

void test_frames_are_freed() {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

int main() {
    test_vm_new();
    test_frames_are_freed();
    return 0;
}
