#include <assert.h>
#include "coord.h"

struct Coordinate new_coord(int x, int y, int z) {
    struct Coordinate coordinate = {
        .x = x,
        .y = y,
        .z = z
    };
    return coordinate;
}

void test_new_coordinate1() {
    struct Coordinate c = new_coord(1, 2, 3);
    assert(c.x == 1);
    assert(c.y == 2);
    assert(c.z == 3);
}

void test_new_coordinate2() {
    struct Coordinate c = new_coord(4, 2, 0);
    assert(c.x == 4);
    assert(c.y == 2);
    assert(c.z == 0);
}

int main() {
    test_new_coordinate1();
    test_new_coordinate2();

    return 0;
}
