#include <stdio.h>
#include <stdlib.h>

#include "binary_search.h"
#include "MinUnit/minunit.h"

static char * test_binary_search_find_first() {
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int idx = binary_search(1, v, sizeof(v)/sizeof(int));

    mu_assert("error, test_binary_search_find_first -> idx != 0", idx == 0);

    return 0;
}

static char * test_binary_search_find_last() {
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int idx = binary_search(10, v, sizeof(v)/sizeof(int));

    mu_assert("error, test_binary_search_find_last -> idx != 9", idx == 9);

    return 0;
}

static char * test_binary_search_find_middle() {
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int idx = binary_search(5, v, sizeof(v)/sizeof(int));

    mu_assert("error, test_binary_search_find_middle -> idx != 4", idx == 4);

    return 0;
}

static char * test_binary_search_not_found() {
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int idx = binary_search(11, v, sizeof(v)/sizeof(int));

    mu_assert("error, test_binary_search_not_found -> idx != -1", idx == -1);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_binary_search_find_first);
    mu_run_test(test_binary_search_find_last);
    mu_run_test(test_binary_search_find_middle);
    mu_run_test(test_binary_search_not_found);
    return 0;
}

int tests_run = 0;

int main() {
    char *result = all_tests();

    printf("binary_search_test.c\n");
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
