#include <stdio.h>
#include <stdlib.h>

#include "shell_sort.h"
#include "MinUnit/minunit.h"

static char * test_shell_sort_all_decreasing() {
    int A_ordered[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int A[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int length = sizeof(A_ordered)/sizeof(int);

    shell_sort(A, length);

    int equal = 1, i = 0;
    for (; i < length; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_shell_sort_all_decreasing -> not equal", equal);

    return 0;
}

static char * test_shell_sort_sorted() {
    int A_ordered[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length = sizeof(A_ordered)/sizeof(int);

    shell_sort(A, length);

    int equal = 1, i = 0;
    for (; i < length; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_shell_sort_sorted -> not equal", equal);

    return 0;
}

static char * test_shell_sort_randomized() {
    int A_ordered[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int A[] = {3, 2, 8, 10, 7, 9, 5, 1, 6, 4};
    int length = sizeof(A_ordered)/sizeof(int);

    shell_sort(A, length);

    int equal = 1, i = 0;
    for (; i < length; i++) {
        equal = A[i] == A_ordered[i];
        if (!equal) break;
    }

    mu_assert("error, test_shell_sort_randomized -> not equal", equal);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_shell_sort_all_decreasing);
    mu_run_test(test_shell_sort_sorted);
    mu_run_test(test_shell_sort_randomized);
    return 0;
}

int tests_run = 0;

int main() {
    char *result = all_tests();

    printf("shell_sort_test.c\n");
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
