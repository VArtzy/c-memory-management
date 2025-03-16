#include <assert.h>
#include "coord.h"

coordinate_t new_coord(int x, int y, int z) {
    coordinate_t coordinate = {
        .x = x,
        .y = y,
        .z = z
    };
    return coordinate;
}

coordinate_t scale_coordinate(struct Coordinate coord, int factor) {
    coordinate_t scaled_coord = {
        .x = coord.x * factor,
        .y = coord.y * factor,
        .z = coord.z * factor
    };
    return scaled_coord;
}

void test_new_coordinate() {
    coordinate_t c = new_coord(1, 2, 3);
    assert(c.x == 1);
    assert(c.y == 2);
    assert(c.z == 3);
}

void test_scale_coordinate() {
    coordinate_t c = new_coord(1, 2, 3);
    coordinate_t scaled = scale_coordinate(c, 2);
    assert(scaled.x == 2);
    assert(scaled.y == 4);
    assert(scaled.z == 6);
}

int main() {
    test_new_coordinate();
    test_scale_coordinate();
    return 0;
}
