#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "insertion_sort.h"
#include "MinUnit/minunit.h"

static char * test_insertion_all_decreasing() {
    int length = 5;
    int * A = malloc(length * sizeof(int));
    int * A_ordered = malloc(length * sizeof(int));
    int i = 0;
    for (; i < 5; ++i) {
        A[i] = -i; // decreasing order, 0, -1, -2...
        A_ordered[5 - i - 1] = -i;
    }

    insertion_sort(A, length);

    int equal = 1;
    for (i = 0; i < 5; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_insertion_all_decreasing -> not equal", equal);

    free(A);
    free(A_ordered);

    return 0;
}

static char * test_insertion_random() {
    int length = 5;

    int * A = malloc(length * sizeof(int));
    A[0] = 4; A[1] = 1; A[2] = 7; A[3] = 2; A[4] = 8;

    int * A_ordered = malloc(length * sizeof(int));
    A_ordered[0] = 1; A_ordered[1] = 2; A_ordered[2] = 4; A_ordered[3] = 7; A_ordered[4] = 8;

    insertion_sort(A, length);

    int equal = 1;
    int i = 0;
    for (i = 0; i < 5; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_insertion_random -> not equal", equal);

    free(A);
    free(A_ordered);

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
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}