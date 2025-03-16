#include <stdio.h>
#include "exercise.h"

void print_numbers_reverse(int start, int end) {
    do {
        printf("%d\n", start);
        start--;
    } while (start >= end);
}

void test(int start, int end){
  printf("Printing from %d to %d:\n", start, end);
  print_numbers_reverse(start, end);
  printf("======================\n");
}

int main() {
  test(5, 1);
  test(1, 5);
}
