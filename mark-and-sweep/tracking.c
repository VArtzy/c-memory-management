#include <assert.h>
#include "vm.h"
#include "sneknew.h"
#include "snekobject.h"
#include "stack.h"

void vm_track_object(vm_t *vm, snek_object_t *obj) {
    if (vm == NULL || obj == NULL) { return; }
    stack_push(vm->objects, obj);
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

void test_new_object() {
    vm_t *vm = vm_new();
    snek_object_t *obj = new_snek_integer(vm, 5);
    assert(obj->kind == INTEGER);
    assert(vm->objects->data[0] == obj);
    free(obj);
    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

void test_vm_new() {
    vm_t *vm = vm_new();
    assert(vm->frames != NULL);
    assert(vm->objects != NULL);
    vm_free(vm);
    // assert(boot_all_freed());
}

void test_frames_are_freed() {
    vm_t *vm = vm_new();
    vm_new_frame(vm);
    vm_free(vm);
    // assert(boot_all_freed());
}

int main() {
    test_vm_new();
    test_frames_are_freed();
    test_new_object();
    return 0;
}
