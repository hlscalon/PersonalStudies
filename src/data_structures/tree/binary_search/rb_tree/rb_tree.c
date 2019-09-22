#include <stdio.h>
#include "rb_tree.h"

Node * rb_create_node(int value, Node * nil) {
    Node * x = malloc(sizeof(Node));
    x->parent = nil;
    x->left = nil;
    x->right = nil;
    x->color = BLACK;
    x->value = value;

    return x;
}

Tree * rb_create_tree() {
	Tree * T = malloc(sizeof(Tree));
	T->nil = rb_create_node(-1, NULL);
	T->root = T->nil;

	return T;
}

void rb_insert(Tree * T, Node * z) {
	Node * y = T->nil;
	Node * x = T->root;
	while (x != T->nil) {
		y = x;
		if (z->value < x->value) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;
	if (y == T->nil) {
		T->root = z;
	} else if (z->value < y->value) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = T->nil;
	z->right = T->nil;
	z->color = RED;

	rb_insert_fixup(T, z);
}

void rb_insert_fixup(Tree * T, Node * z) {
	Node * y;
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y->color == RED) {
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
			y = z->parent->parent->left;
			if (y->color == RED) {
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

	T->root->color = BLACK;
}

void rb_left_rotate(Tree * T, Node * x) {
	Node * y = x->right;
	x->right = y->left;
	if (y->left != T->nil) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == T->nil) {
		T->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void rb_right_rotate(Tree * T, Node * x) {
	Node * y = x->left;
	x->left = y->right;
	if (y->right != T->nil) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == T->nil) {
		T->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

Node * rb_search(Tree * T, int value) {
	Node * x = T->root;
	while (x != T->nil && value != x->value) {
		if (value < x->value) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	return x;
}

void rb_print(Tree * T, Node * x) {
	if (x == T->nil) return;

	printf("Node = %d", x->value);
	if (x->parent != T->nil) {
		printf(" -> Parent = %d", x->parent->value);
	}

	printf("\n");

	rb_print(T, x->left);
	rb_print(T, x->right);
}

void rb_transplant(Tree * T, Node * u, Node * v) {
	if (u->parent == T->nil) {
		T->root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	v->parent = u->parent;
}

Node * rb_tree_minimum(Tree * T, Node * n) {
	Node * x = n;
	while (x->left != T->nil) {
		x = x->left;
	}

	return x;
}

void rb_delete_fixup(Tree * T, Node * x) {
	Node * w;
	while (x != T->root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;

				rb_left_rotate(T, x->parent);
				w = x->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else if (w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;

				rb_right_rotate(T, w);
				w = x->parent->right;
				w->color = x->parent->color;
				x->parent->color = BLACK;
			}

			w->right->color = BLACK;
			rb_left_rotate(T, x->parent);
			x = T->root;
		} else {
			w = x->parent->left;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;

				rb_right_rotate(T, x->parent);
				w = x->parent->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else if (w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;

				rb_left_rotate(T, w);
				w = x->parent->left;
				w->color = x->parent->color;
				x->parent->color = BLACK;
			}

			w->left->color = BLACK;
			rb_right_rotate(T, x->parent);
			x = T->root;
		}
	}

	x->color = BLACK;
}

void rb_delete(Tree * T, Node * z) {
	Node * y = z;
	Color y_original_color = y->color;
	Node * x;

	if (z->left == T->nil) {
		x = z->right;
		rb_transplant(T, z, z->right);
	} else if (z->right == T->nil) {
		x = z->left;
		rb_transplant(T, z, z->left);
	} else {
		y = rb_tree_minimum(T, z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		} else {
			rb_transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rb_transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (y_original_color == BLACK) {
		rb_delete_fixup(T, x);
	}
}
