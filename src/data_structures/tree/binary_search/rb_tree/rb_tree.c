#include <stdio.h>
#include "rb_tree.h"

Node * rb_create_node(int value) {
    Node * x = malloc(sizeof(Node));
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->color = BLACK;
    x->value = value;

    return x;
}

void rb_insert(Node * T, Node * z) {
	Node * y = NULL;
	Node * x = T;
	while (x != NULL) {
		y = x;
		if (z->value < x->value) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;
	if (y == NULL) {
		T = z;
	} else if (z->value < y->value) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = NULL;
	z->right = NULL;
	z->color = RED;

	rb_insert_fixup(T, z);
}

void rb_insert_fixup(Node * T, Node * z) {
	Node * y = NULL;
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y != NULL && y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else if (z == z->parent->right) {
				z = z->parent;
				rb_left_rotate(T, z);
			} else {
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rb_right_rotate(T, z->parent->parent);
			}
		} else {
			if (z->parent == z->parent->parent->right) {
				y = z->parent->parent->left;
				if (y != NULL && y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else if (z == z->parent->left) {
					z = z->parent;
					rb_right_rotate(T, z);
				} else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rb_left_rotate(T, z->parent->parent);
				}
			}
		}
	}

	T->color = BLACK;
}

void rb_left_rotate(Node * T, Node * x) {
	Node * y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL) {
		T = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void rb_right_rotate(Node * T, Node * x) {
	Node * y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL) {
		T = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

Node * rb_search(Node * T, int value) {
	Node * x = T;
	while (x != NULL && value != x->value) {
		if (value < x->value) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	return x;
}

void rb_print(Node * x) {
	if (x == NULL) return;

	printf("Node = %d\n", x->value);

	rb_print(x->left);
	rb_print(x->right);
}
