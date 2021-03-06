#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rb_tree.h"
#include "MinUnit/minunit.h"

static char * test_rb_tree_search() {
    Tree * T = rb_create_tree();

    Node * n2 = rb_create_node(11, T->nil);
    rb_insert(T, n2);

    Node * n3 = rb_create_node(1, T->nil);
    rb_insert(T, n3);

    Node * n4 = rb_create_node(2, T->nil);
    rb_insert(T, n4);

    Node * n1 = rb_create_node(7, T->nil);
    rb_insert(T, n1);

    Node * n5 = rb_create_node(5, T->nil);
    rb_insert(T, n5);

    Node * n6 = rb_create_node(8, T->nil);
    rb_insert(T, n6);

    Node * n7 = rb_create_node(14, T->nil);
    rb_insert(T, n7);

    Node * n8 = rb_create_node(4, T->nil);
    rb_insert(T, n8);

    Node * n9 = rb_create_node(15, T->nil);
    rb_insert(T, n9);

    // printf("Printing tree 1...\n");
    // rb_print(T, T->root);
    // printf("Finished successfully\n");

    Node * x = rb_search(T, 50);
    int found = x != T->nil;

    mu_assert("error, test_rb_tree_search -> found 50", !found);

    x = rb_search(T, 4);
    found = x != T->nil;

    mu_assert("error, test_rb_tree_search -> not found 4", found);
    mu_assert("error, test_rb_tree_search -> T root not equal 7", T->root->value == 7);

    rb_delete(T, n6); // 8

    // printf("Printing tree 2...\n");
    // rb_print(T, T->root);
    // printf("Finished successfully\n");

    // root keeps 7
    mu_assert("error, test_rb_tree_search -> T root not equal 7", T->root->value == 7);

    // root's right descendant is now 14
    mu_assert("error, test_rb_tree_search -> T root descendant not equal 14", T->root->right->value == 14);

    free(n9);
    free(n8); free(n7); free(n6);
    free(n5); free(n4); free(n3);
    free(n2); free(n1);
    free(T->nil); free(T);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_rb_tree_search);
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