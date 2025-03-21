#include <assert.h>
#include "coordinate.h"

void coordinate_update_x(coordinate_t coord, int new_x) {
    coord.x = new_x;
}

coordinate_t coordinate_update_and_return_x(coordinate_t coord, int new_x) {
    coord.x = new_x;
    return coord;
}

coordinate_t new_coordinate(int x, int y, int z) {
    return (coordinate_t){.x = x, .y = y, .z = z};
}

void test_unchanged() {
    coordinate_t old = new_coordinate(1, 2, 3);
    assert(old.x == 1);

    coordinate_update_x(old, 4);
    assert(old.x == 1);
}

void test_changed() {
    coordinate_t old = new_coordinate(1, 2, 3);
    assert(old.x == 1);

    coordinate_t new = coordinate_update_and_return_x(old, 4);
    assert(new.x == 4);
    assert(old.x == 1);
    assert(&old != &new);
}

int main() {
    test_unchanged();
    test_changed();
    return 0;
}
