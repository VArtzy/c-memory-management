#include <assert.h>
#include "exercise.h"


float snek_score(
  int num_files,
  int num_contributors,
  int num_commits,
  float avg_bug_criticality
) {
    int size_factor = num_files * num_commits;
    int complexity_factor = size_factor + num_contributors;
    float final_score = complexity_factor * avg_bug_criticality;
    return final_score;
}

void test_snek_score_1() {
    float result = snek_score(3, 4, 5, 0.1);
    assert(result == 1.9f);  // Use 'f' suffix to compare floats
}

void test_snek_score_2() {
    float result = snek_score(10, 10, 10, 0.1);
    assert(result == 11.0f);  // Use 'f' suffix to compare floats
}

void test_snek_score_3() {
    float result = snek_score(105, 205, 207, 0.1);
    assert(result == 2194.0f);  // Use 'f' suffix to compare floats
}

int main() {
    test_snek_score_1();
    test_snek_score_2();
    test_snek_score_3();

    return 0;
}
