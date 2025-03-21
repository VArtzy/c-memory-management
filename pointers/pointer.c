#include <stdio.h>

// %p denotes address (short for `p`ointer), %d denotes `d`ecimal
int main() {
    int age = 32;
    int *pointer_to_age = &age; // `&` is address-of operator, giving the address of value live that can be saved to a pointer
    int to_age = &age; // `to_age` is same as `*pointer_to_age`
    printf("%p\n", &age);
    printf("%d\n", &age);
    printf("%p\n", to_age);
    printf("%d\n", to_age);
    printf("%p\n", pointer_to_age);
    printf("%d\n", pointer_to_age);

    int meaning_of_life = 42;
    int *pointer_to_mol = &meaning_of_life;
    int at_pointer = pointer_to_mol;
    int value_at_pointer = *pointer_to_mol;
    printf("%d\n", at_pointer); // `at_pointer` is same as `pointer_to_mol`
    printf("%d", value_at_pointer);

    // bedain antara `pointer` dengan `deference` karena mereka punya simbol yang sama (*)
    // rule of thumb: pointer sebelah kirinya ada type (ex: `int *`) sedangkan deference tidak ada (ex: `*pointer`)
}
