#include "vm.h"
#include "stack.h"

#include <assert.h>
#include <stdlib.h>
#include "sneknew.h"
#include "snekobject.h"

void trace(vm_t *vm) {
    if (vm == NULL) { return; }

    stack_t *gray_objects = stack_new(8);
    if (gray_objects == NULL) { return; }

    for (int i = 0; i < vm->objects->count; i++) {
        snek_object_t *obj = vm->objects->data[i];
        if (obj && obj->is_marked) {
            stack_push(gray_objects, obj);
        }
    }

    while(gray_objects->count > 0) {
        snek_object_t *obj = stack_pop(gray_objects);
        trace_blacken_object(gray_objects, obj);
    }

    stack_free(gray_objects);
}

void trace_blacken_object(stack_t *gray_objects, snek_object_t *obj) {
    if (obj == NULL) { return; }

    switch(obj->kind) {
        case INTEGER: return;
        case FLOAT: return;
        case STRING: return;
        case VECTOR3: {
          trace_mark_object(gray_objects, obj->data.v_vector3.x);
          trace_mark_object(gray_objects, obj->data.v_vector3.y);
          trace_mark_object(gray_objects, obj->data.v_vector3.z);
          break;
        }
        case ARRAY: {
          snek_array_t arr = obj->data.v_array;
          for (int i = 0; i < arr.size; i++) {
              trace_mark_object(gray_objects, snek_array_get(obj, i));
          }
          break;
        }
    }
}

void trace_mark_object(stack_t *gray_objects, snek_object_t *obj) {
    if (obj == NULL) { return; }
    if (obj->is_marked) { return; }

    obj->is_marked = true;
    stack_push(gray_objects, (void *)obj);
}

// don't touch below this line

void mark(vm_t *vm) {
  for (size_t i = 0; i < vm->frames->count; i++) {
    frame_t *frame = vm->frames->data[i];
    for (size_t j = 0; j < frame->references->count; j++) {
      snek_object_t *obj = frame->references->data[j];
      obj->is_marked = true;
    }
  }
}

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

void test_trace_vector() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *x = new_snek_integer(vm, 5);
    snek_object_t *y = new_snek_integer(vm, 5);
    snek_object_t *z = new_snek_integer(vm, 5);
    snek_object_t *vector = new_snek_vector3(vm, x, y, z);

    assert(!x->is_marked);
    assert(!y->is_marked);
    assert(!z->is_marked);
    assert(!vector->is_marked);

    frame_reference_object(frame, vector);
    mark(vm);
    assert(vector->is_marked);
    assert(!x->is_marked);
    assert(!y->is_marked);
    assert(!z->is_marked);

    trace(vm);
    assert(vector->is_marked);
    assert(x->is_marked);
    assert(y->is_marked);
    assert(z->is_marked);

    vm_free(vm);
    // Assuming `boot_all_freed` is implemented elsewhere
    // assert(boot_all_freed());
}

void test_trace_array() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *devs = new_snek_array(vm, 2);
    snek_object_t *lane = new_snek_string(vm, "Lane");
    snek_object_t *teej = new_snek_string(vm, "Teej");
    snek_array_set(devs, 0, lane);
    snek_array_set(devs, 1, teej);

    assert(!devs->is_marked);
    assert(!lane->is_marked);
    assert(!teej->is_marked);

    frame_reference_object(frame, devs);
    mark(vm);
    assert(devs->is_marked);
    assert(!lane->is_marked);
    assert(!teej->is_marked);

    trace(vm);
    assert(devs->is_marked);
    assert(lane->is_marked);
    assert(teej->is_marked);

    vm_free(vm);
    // assert(boot_all_freed());
}

void test_trace_nested() {
    vm_t *vm = vm_new();
    frame_t *frame = vm_new_frame(vm);

    snek_object_t *bootdevs = new_snek_array(vm, 2);
    snek_object_t *lane = new_snek_string(vm, "Lane");
    snek_object_t *hunter = new_snek_string(vm, "Hunter");
    snek_array_set(bootdevs, 0, lane);
    snek_array_set(bootdevs, 1, hunter);

    snek_object_t *terminaldevs = new_snek_array(vm, 4);
    snek_object_t *prime = new_snek_string(vm, "Prime");
    snek_object_t *teej = new_snek_string(vm, "Teej");
    snek_object_t *dax = new_snek_string(vm, "Dax");
    snek_object_t *adam = new_snek_string(vm, "Adam");
    snek_array_set(terminaldevs, 0, prime);
    snek_array_set(terminaldevs, 1, teej);
    snek_array_set(terminaldevs, 2, dax);
    snek_array_set(terminaldevs, 3, adam);

    snek_object_t *alldevs = new_snek_array(vm, 2);
    snek_array_set(alldevs, 0, bootdevs);
    snek_array_set(alldevs, 1, terminaldevs);

    frame_reference_object(frame, alldevs);
    mark(vm);
    trace(vm);

    assert(bootdevs->is_marked);
    assert(lane->is_marked);
    assert(hunter->is_marked);
    assert(terminaldevs->is_marked);
    assert(prime->is_marked);
    assert(teej->is_marked);
    assert(dax->is_marked);
    assert(adam->is_marked);
    assert(alldevs->is_marked);

    vm_free(vm);
    // assert(boot_all_freed());
}

int main() {
    test_trace_vector();
    test_trace_array();
    test_trace_nested();
    return 0;
}
