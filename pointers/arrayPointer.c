#include <stdio.h>

int main() {
    int numbers[5] = {1, 2, 3, 4, 5}; // REMEMBER! array name decays to `pointer` of the first element
    /**
     * In many contexts, arrays decay to pointers, array name becomes "just" a pointer to first element of array.
     * Unlike struct, union or any types -- array name decays to a `pointer` by default.
     * This make an exception to our rule of thumb in `pointer.c` before.
     * It is pointer if it has (*) before it's type AND if it is an array name.
     * Array have to decay to pointer due as easiest way to create sequential bunch of value (can do indexing, etc)
     * Whereas indexing is actually just pointer arithmetic under the hood.
     * coordinate_t point = {10, 20, 30}; Struct is a struct (value), not pointer, unlike array!
     * This is why your struct manipulation doesnt work, it manipulates `value` whereas array manipulates `pointer`.
     * SO, remember the difference between pointer, address, value and dereference to get value!
     * to make you clear about pointer concept :D 
     */

    printf("numbers[0] = %d\n", numbers[0]); // arrays in C are zero-based index meaning that index start from 0

    printf("*(numbers + 0) = %d\n", *(numbers)); // is address of first number + n * int_size to get new address

    int *ptr = numbers;
    printf("numbers %d\n", numbers); // warning, `numbers` is a pointer! (point to the first number of the array)
    printf("numbers %p\n", ptr); // printing pointer's address
    printf("numbers ptr %d\n", *ptr); // dereference pointer and print the value
    
    // Pointer arithmetic
    ptr += 2; // adding 2 to the address of numbers (the first element in the array) resulting address of 3
    printf("numbers ptr += 2 %d\n", *ptr);
}
