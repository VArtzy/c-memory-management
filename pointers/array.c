#include <assert.h>
#include "exercise.h"

void update_file(int filedata[200], int new_filetype, int new_num_lines){
    filedata[1] = new_num_lines;
    filedata[2] = new_filetype;
    filedata[199] = 0;
}

void test_update_file_basic() {
    int filedata[200] = {0};
    update_file(filedata, 1, 100);
    assert(filedata[1] == 100);
    assert(filedata[2] == 1);
    assert(filedata[199] == 0);
}

void test_update_file_different_values() {
    int filedata[200] = {0};
    for (int i = 0; i < 200; i++) {
        filedata[i] = 69;
    }
    update_file(filedata, 3, 250);
    assert(filedata[1] == 250);
    assert(filedata[2] == 3);
    assert(filedata[199] == 0);
}

int main() {
    test_update_file_basic();
    test_update_file_different_values();
    return 0;
}
