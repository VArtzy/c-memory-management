#include <assert.h>
#include "coord.h"

void test_new_coordinate1() {
    struct Coordinate c;
    c.x = 1;
    c.y = 2;
    c.z = 3;

    assert(c.x == 1);
    assert(c.y == 2);
    assert(c.z == 3);
}

void test_new_coordinate2() {
    struct Coordinate c;
    c.x = 4;
    c.y = 2;
    c.z = 0;

    assert(c.x == 4);
    assert(c.y == 2);
    assert(c.z == 0);
}

void test_new_coordinate3() {
    struct Coordinate c;
    c.x = 10;
    c.y = 20;
    c.z = 30;

    assert(c.x == 10);
    assert(c.y == 20);
    assert(c.z == 30);
}

void test_new_coordinate4() {
    struct Coordinate c;
    c.x = 0;
    c.y = 6;
    c.z = 9;

    assert(c.x == 0);
    assert(c.y == 6);
    assert(c.z == 9);
}

int main() {
    test_new_coordinate1();
    test_new_coordinate2();
    test_new_coordinate3();
    test_new_coordinate4();

    return 0;
}
