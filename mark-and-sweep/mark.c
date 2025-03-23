#include "vm.h"
#include "snekobject.h"
#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include "sneknew.h"

void mark(vm_t *vm) {
    if (vm == NULL) { return; }
    for (int i = 0; i < vm->frames->count; i++) {
        frame_t *frame = vm->frames->data[i];
        for (int j = 0; j < frame->references->count; j++) {
            snek_object_t *obj = frame->references->data[j];
            obj->is_marked = true;
        }
    }
}

// don't touch below this line

void frame_reference_object(frame_t *frame, snek_object_t *obj) {
  stack_push(frame->references, obj);
}

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
  // Free the stack frames, and then their container
  for (int i = 0; i < vm->frames->count; i++) {
    frame_free(vm->frames->data[i]);
  }
  stack_free(vm->frames);

  // Free the objects, and then their container
  for (int i = 0; i < vm->objects->count; i++) {
    snek_object_free(vm->objects->data[i]);
  }
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

void vm_track_object(vm_t *vm, snek_object_t *obj) {
  stack_push(vm->objects, obj);
}

void test_single_frame() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *teej_skill = new_snek_integer(vm, 420);
    snek_object_t *lane_skill = new_snek_string(vm, "issues");

    mark(vm);
    assert(!teej_skill->is_marked);
    assert(!lane_skill->is_marked);

    frame_reference_object(frame, teej_skill);
    frame_reference_object(frame, lane_skill);

    mark(vm);
    assert(teej_skill->is_marked);
    assert(lane_skill->is_marked);

    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

void test_multi_frame() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);
    frame_t *frame2 = vm_new_frame(vm);

    snek_object_t *teej_skill = new_snek_integer(vm, 420);
    snek_object_t *lane_skill = new_snek_string(vm, "issues");
    snek_object_t *prime_skill = new_snek_string(vm, "infinite");

    frame_reference_object(frame, teej_skill);
    frame_reference_object(frame, lane_skill);
    frame_reference_object(frame2, prime_skill);
    mark(vm);

    assert(teej_skill->is_marked);
    assert(lane_skill->is_marked);
    assert(prime_skill->is_marked);

    vm_free(vm);
    // assert(boot_all_freed());
}

int main() {
    test_single_frame();
    test_multi_frame();
    return 0;
}
