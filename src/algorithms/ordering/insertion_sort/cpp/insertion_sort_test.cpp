#include <iostream>
#include <vector>

#include "insertion_sort.hpp"
#include "MinUnit/minunit.h"

static char * test_insertion_all_decreasing() {
    std::vector<int> A(5);
    std::vector<int> A_ordered(5);
    for (int i = 0; i < 5; ++i) {
        A[i] = -i; // decreasing order, 0, -1, -2...
        A_ordered[5 - i - 1] = -i;
    }

    insertion_sort(A);

    int equal = 1;
    for (int i = 0; i < 5; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_insertion_all_decreasing -> not equal", equal);

    return 0;
}

static char * test_insertion_random() {
    std::vector<int> A(5);
    A[0] = 4; A[1] = 1; A[2] = 7; A[3] = 2; A[4] = 8;

    std::vector<int> A_ordered(5);
    A_ordered[0] = 1; A_ordered[1] = 2; A_ordered[2] = 4; A_ordered[3] = 7; A_ordered[4] = 8;

    insertion_sort(A);

    int equal = 1;
    for (int i = 0; i < 5; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_insertion_random -> not equal", equal);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_insertion_all_decreasing);
    mu_run_test(test_insertion_random);
    return 0;
}

int tests_run = 0;

int main() {
    char *result = all_tests();

    std::cout << "insertion_sort_test.c\n";
    if (result != 0) {
        std::cout << result << "\n";
    } else {
        std::cout << "ALL TESTS PASSED\n";
    }

    std::cout << "Tests run: " << tests_run << "\n";

    return result != 0;
}
