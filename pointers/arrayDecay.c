#include <stdio.h>

/**
 * As mention in `arraypointer.c`,
 * So we know that arrays are like pointers, but they're not exactly the same. Arrays allocate memory for all their elements, whereas pointers just hold the address of a memory location. In many contexts, arrays decay to pointers, meaning the array name becomes "just" a pointer to the first element of the array.
 * And also when they're passed to functions... so they actually decay quite often in practice. That's why you can't pass an array to a function by value like you do with a struct; instead, the array name decays to a pointer.
*/

/**
 * When Arrays Don't Decay
1. sizeof Operator: Returns the size of the entire array (e.g., sizeof(arr)), not just the size of a pointer.
2. & Operator Taking the address of an array with &arr gives you a pointer to the whole array, not just the first element. The type of &arr is a pointer to the array type, e.g., int (*)[5] for an int array with 5 elements.
3. Initialization: When an array is declared and initialized, it is fully allocated in memory and does not decay to a pointer.
*/
void core_utils_func(int core_utilization[]) {
    printf("sizeof core_utilization in core_utils_func: %zu", sizeof(core_utilization)); // sizeof pointer
}

// don't touch below this line

int main() {
  int arr[5];
  int *ptr = arr; // 'arr' decays to 'int*'
  int value = *(arr + 1); // 'arr' decays to 'int*'
  printf("pointer: %p\n", arr);
  printf("pointer: %p\n", ptr);
  printf("value: %d\n", value);

  int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12, 11};
  int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
  printf("sizeof core_utilization in main: %zu\n", sizeof(core_utilization));
  printf("len of core_utilization: %d\n", len); // sizeof len(core_utilization)
  core_utils_func(core_utilization); // sizeof core_utilization
  return 0;
}
