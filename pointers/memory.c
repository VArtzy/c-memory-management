#include <assert.h>
#include "snek.h"

unsigned long size_of_addr(long long i){
  unsigned long sizeof_snek_version = sizeof(&i);
  return sizeof_snek_version;
}

void size_of_addr_16() {
    unsigned long size = size_of_addr(16);
    assert(size == 8);
}

void size_of_addr_32() {
    unsigned long size = size_of_addr(32);
    assert(size == 8);
}

void size_of_addr_64() {
    unsigned long size = size_of_addr(64);
    assert(size == 8);
}

void size_of_addr_128() {
    unsigned long size = size_of_addr(128);
    assert(size == 8);
}

int main() {
    size_of_addr_16();
    size_of_addr_32();
    size_of_addr_64();
    size_of_addr_128();
    return 0;
}
