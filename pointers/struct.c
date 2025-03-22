#include <stdio.h>
#include "coordinate.h"

int main() {
    coordinate_t point = {10, 20, 30}; // Struct is a struct, not pointer, unlike array!
    printf("x: %d\n", point.x);

    coordinate_t *ptrToPoint = &point;
    printf("x: %d\n", ptrToPoint->x); // can't use (.) on pointer, it is not a struct. Use arrow operator instead
    
    printf("x: %d\n", (*ptrToPoint).x); // dereference, then access the struct value. Having output same as above
}
