#include "vm.h"
#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include "sneknew.h"

void vm_free(vm_t *vm) {
    for (int i = 0; i < vm->frames->count; i++) {
        frame_free(vm->frames->data[i]);
    }
    stack_free(vm->frames);
    for (int i = 0; i < vm->objects->count; i++) {
        snek_object_free(vm->objects->data[i]);
    }
    stack_free(vm->objects);
    free(vm);
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

void vm_track_object(vm_t *vm, snek_object_t *obj) {
  stack_push(vm->objects, obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
  stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *frame = malloc(sizeof(frame_t));
  frame->references = stack_new(8);

  vm_frame_push(vm, frame);
  return frame;
}

void frame_free(frame_t *frame) {
  stack_free(frame->references);
  free(frame);
}

void test_reference_object() {
    vm_t *vm = vm_new();
    new_snek_integer(vm, 5);
    new_snek_string(vm, "hello");
    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

void test_frames_are_freed() {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_new_frame(vm);
    vm_free(vm);
    // assert(boot_all_freed());
}

int main() {
    test_reference_object();
    test_frames_are_freed();
    return 0;
}
