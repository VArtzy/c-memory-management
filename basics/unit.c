#include <assert.h>
#include "exercise.h"

float get_average(int x, int y, int z) {
    return (float)(x + y + z) / 3;
}

void test_get_average() {
    float result = get_average(3, 4, 5);
    assert(result == 4.0f);  // Use 'f' suffix to compare floats
}

void test_non_integer() {
    float result = get_average(3, 3, 5);
    float expected = 11.0f / 3.0f;  // Calculate expected value
    assert(result == expected);  // Compare floating-point values
}

void test_average_of_same() {
    float result = get_average(10, 10, 10);
    assert(result == 10.0f);  // Use 'f' suffix to compare floats
}

void test_average_of_big_numbers() {
    float result = get_average(1050, 2050, 2075);
    assert(result == 1725.0f);  // Use 'f' suffix to compare floats
}

int main() {
    test_get_average();
    test_non_integer();
    test_average_of_same();
    test_average_of_big_numbers();

    return 0;
}
