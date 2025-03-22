#include "coordinate.h"
#include <stdio.h>

int main() {
    coordinate_t points[3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    printf("points[1].x = %d, points[1].y = %d, points[z].z = %d\n", points[1].x, points[1].y, points[1].z);

    // using pointer
    coordinate_t *ptr = points;
    printf("ptr[1].x = %d, ptr[1].y = %d, ptr[z].z = %d\n", (ptr + 1)->x, (ptr + 1)->y, (ptr + 1)->z);
}
