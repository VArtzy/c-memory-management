#include <string.h>
#include <stdio.h>

int main() {
    char src[] = "Hello";
    char dest[6];
    strcpy(dest, src);
    printf("%s\n", dest);

    char str1[12] = "Hello";
    char *str2 = " World";
    strcat(str1, str2);
    printf("%s\n", str1);

    char str[] = "Hello";
    size_t len = strlen(str);
    printf("len is %d\n", len);

    char str3[] = "Hello";
    char str4[] = "World";
    int result = strcmp(str3, str4);
    printf("%d\n", result);

    char str5[] = "Hello";
    char str6[6];
    strncpy(str6, str5, 3);
    str6[3] = '\0'; // ensure null termination
    printf("%s\n", str6);

    char str7[12] = "Hello";
    char str8[] = " World";
    strncat(str7, str8, 3);
    printf("%s\n", str7);

    char str9[] = "Hello";
    char *pos = strchr(str9, 'l');
    printf("%p\n", pos);
    printf("%c\n", *pos);

    char str10[] = "Hello World";
    char *pos1 = strstr(str10, "World");
    printf("%p\n", pos1);
    printf("%c\n", *pos1);
}
