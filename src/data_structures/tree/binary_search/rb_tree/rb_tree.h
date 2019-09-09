#ifndef RB_TREE_H
#define RB_TREE_H

// for NULL
#include <stddef.h>

// for malloc()
#include <stdlib.h>

typedef enum Color_s
{
    RED,
    BLACK
} Color;

typedef struct Node_s Node;

struct Node_s {
    Node * parent;
    Node * left;
    Node * right;
    Color color;
    int value;
};

struct Tree_s {
    Node * root;
};

typedef struct Tree_s Tree;

void rb_left_rotate(Tree * T, Node * x);
void rb_right_rotate(Tree * T, Node * x);
void rb_insert(Tree * T, Node * z);
void rb_insert_fixup(Tree * T, Node * z);
void rb_transplant(Tree * T, Node * u, Node * z);
void rb_delete(Tree * T, Node * z);
void rb_print(Node * x);
Node * rb_search(Tree * T, int value);
Node * rb_create_node(int value);
Tree * rb_create_tree();

#endif  // RB_TREE_H
