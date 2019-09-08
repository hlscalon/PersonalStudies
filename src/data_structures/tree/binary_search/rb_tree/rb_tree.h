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

void rb_left_rotate(Node * T, Node * x);
void rb_right_rotate(Node * T, Node * x);
void rb_insert(Node * T, Node * z);
void rb_insert_fixup(Node * T, Node * z);
void rb_transplant(Node * T, Node * u, Node * z);
void rb_delete(Node * T, Node * z);
void rb_print(Node * T);
Node * rb_search(Node * T, int value);
Node * rb_create_node(int value);

#endif  // RB_TREE_H
