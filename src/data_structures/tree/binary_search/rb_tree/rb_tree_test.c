#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rb_tree.h"
#include "MinUnit/minunit.h"

static char * test_rb_tree_search_found() {
    Node * T = rb_create_node(15);

    Node * n1 = rb_create_node(7);
    rb_insert(T, n1);

    Node * n2 = rb_create_node(11);
    rb_insert(T, n2);

    Node * n3 = rb_create_node(1);
    rb_insert(T, n3);

    Node * n4 = rb_create_node(2);
    rb_insert(T, n4);

    Node * n5 = rb_create_node(5);
    rb_insert(T, n5);

    Node * n6 = rb_create_node(8);
    rb_insert(T, n6);

    Node * n7 = rb_create_node(14);
    rb_insert(T, n7);

    Node * n8 = rb_create_node(4);
    rb_insert(T, n8);

    // rb_print(T);

    Node * x = rb_search(T, 5);
    int found = x != NULL;

    free(n8); free(n7); free(n6);
    free(n5); free(n4); free(n3); free(n2);
    free(n1); free(T);

    mu_assert("error, test_rb_tree_search_found -> not found", !found);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_rb_tree_search_found);
    return 0;
}

int tests_run = 0;

int main() {
    char *result = all_tests();

    printf("rb_tree_test.c\n");
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}