#include <stdio.h>
#include <string.h>

int main() {
    char first[50] = "Snek"; // declare using array
    char *second = "lang!"; // declare using pointer

    printf("%s %s\n", first, second);
    strcat(first, second);
    printf("Hello, %s\n", first);
    printf("Sizeof first: %zu\n", sizeof(first));
}
