#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quicksort.h"
#include "MinUnit/minunit.h"

static char * test_quicksort_all_decreasing() {
    int length = 8;
    int * A = malloc(length * sizeof(int));
    int * A_ordered = malloc(length * sizeof(int));

    A[0] = A_ordered[7] = 7;
    A[1] = A_ordered[6] = 6;
    A[2] = A_ordered[5] = 5;
    A[3] = A_ordered[4] = 4;
    A[4] = A_ordered[3] = 3;
    A[5] = A_ordered[2] = 2;
    A[6] = A_ordered[1] = 1;
    A[7] = A_ordered[0] = 0;

    quicksort(A, 0, length - 1);

    int equal = 1;
    int i;
    for (i = 0; i < length; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_quicksort_all_decreasing -> not equal", equal);

    free(A);
    free(A_ordered);

    return 0;
}

static char * test_quicksort_randomized() {
    int length = 8;
    int * A = malloc(length * sizeof(int));
    int * A_ordered = malloc(length * sizeof(int));

    A[0] = 7; A[1] = 2; A[2] = 1; A[3] = 3; A[4] = 4; A[5] = 5; A[6] = 0; A[7] = 6;
    A_ordered[0] = 0; A_ordered[1] = 1; A_ordered[2] = 2; A_ordered[3] = 3; A_ordered[4] = 4; A_ordered[5] = 5; A_ordered[6] = 6; A_ordered[7] = 7;

    quicksort(A, 0, length - 1);

    int equal = 1;
    int i;
    for (i = 0; i < length; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_quicksort_randomized -> not equal", equal);

    free(A);
    free(A_ordered);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_quicksort_all_decreasing);
    mu_run_test(test_quicksort_randomized);
    return 0;
}

int tests_run = 0;

int main() {
    char *result = all_tests();

    printf("quicksort_test.c\n");
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}