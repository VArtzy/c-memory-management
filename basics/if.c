#include <assert.h>
#include "exercise.h"
#include <string.h>

char *get_temperature_status(int temp) {
    if (temp < 70) {
        return "too cold";
    } else if (temp > 90) {
        return "too hot";
    } else {
        return "just right";
    }
}

void test_cold() {
    char *result = get_temperature_status(50);
    assert(strcmp(result, "too cold") == 0);
}

void test_hot() {
    char *result = get_temperature_status(100);
    assert(strcmp(result, "too hot") == 0);
}

void test_just_right() {
    char *result = get_temperature_status(70);
    assert(strcmp(result, "just right") == 0);
}

void test_just_right2() {
    char *result = get_temperature_status(75);
    assert(strcmp(result, "just right") == 0);
}

int main() {
    test_cold();
    test_hot();
    test_just_right();
    test_just_right2();

    return 0;
}
