#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "exercise.h"

void swap(void *vp1, void *vp2, size_t size) {
    void *tmp = malloc(size); // temp variable as void pointer since we're not know the type and type's size
    if (tmp == NULL) {
        return;
    }
    /*
     * *tmp = *(size_t*)vp1; this wouldnt work because size_t only hold 8 byte in total,
     * this can work in simple swap like int swap or string swap but on struct resulting only first element copied
     * using memcpy to fill the temp variable is the right way since it's automatically swap for any types of thing
    */
    memcpy(tmp, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, tmp, size);
    free(tmp);
}

typedef struct CoffeeShop {
    uint64_t quality;
    uint64_t taste;
    uint64_t branding;
} coffee_shop_t;

void test_generic_ints() {
    int i1 = 1234;
    int i2 = 5678;

    swap(&i1, &i2, sizeof(int));

    assert(i1 == 5678);
    assert(i2 == 1234);
}

void test_generic_strings() {
    char *s1 = "dax";
    char *s2 = "adam";

    swap(&s1, &s2, sizeof(char *));
    assert(strcmp(s1, "adam") == 0);
    assert(strcmp(s2, "dax") == 0);
}

void test_generic_structs() {
    coffee_shop_t sbucks = {2, 3, 4};
    coffee_shop_t terminalshop = {10, 10, 10};

    swap(&sbucks, &terminalshop, sizeof(coffee_shop_t));

    assert(sbucks.quality == 10);
    assert(sbucks.taste == 10);
    assert(sbucks.branding == 10);

    assert(terminalshop.quality == 2);
    assert(terminalshop.taste == 3);
    assert(terminalshop.branding == 4);
}

int main() {
    test_generic_ints();
    test_generic_strings();
    test_generic_structs();
    return 0;
}
