#include <assert.h>
#include "color.h"

void test_color_enum1() {
    assert(RED == 0);
    assert(GREEN == 1);
    assert(BLUE == 2);
}

void test_color_enum2() {
    assert(RED != 4);
    assert(GREEN != 2);
    assert(BLUE != 0);
}

int main() {
    test_color_enum1();
    test_color_enum2();
    return 0;
}
