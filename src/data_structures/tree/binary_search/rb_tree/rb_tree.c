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

Tree * rb_create_tree() {
	Tree * T = malloc(sizeof(Tree));
	T->root = NULL;

	return T;
}

void rb_insert(Tree * T, Node * z) {
	Node * y = NULL;
	Node * x = T->root;
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
		T->root = z;
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

void rb_insert_fixup(Tree * T, Node * z) {
	Node * y = NULL;
	while (z != NULL && z->parent != NULL && z->parent->color == RED && z->parent->parent != NULL) {
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

	T->root->color = BLACK;
}

void rb_left_rotate(Tree * T, Node * x) {
	Node * y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL) {
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
	if (y->right != NULL) {
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL) {
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

	printf("Node = %d", x->value);
	if (x->parent != NULL) {
		printf(" -> Parent = %d", x->parent->value);
	}

	printf("\n");

	rb_print(x->left);
	rb_print(x->right);
}

void rb_transplant(Tree * T, Node * u, Node * v) {
	if (u->parent == NULL) {
		T->root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	if (v != NULL) {
		v->parent = u->parent;
	}
}

Node * rb_tree_minimum(Node * n) {
	if (n == NULL) {
		return NULL;
	}

	Node * x = n;
	while (x->left != NULL) {
		x = x->left;
	}

	return x;
}

void rb_delete_fixup(Tree * T, Node * x) {
	if (x == NULL) {
		return;
	}

	Node * w;
	while (x != NULL && x != T->root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;

				rb_left_rotate(T, x->parent);
				w = x->parent->right;
			}

			if (w->right != NULL) {
				if (w->left != NULL && w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else if (w->right->color == BLACK) {
					if (w->left != NULL) {
						w->left->color = BLACK;
					}

					w->color = RED;

					rb_right_rotate(T, w);
					w = x->parent->right;
					w->color = x->parent->color;
					x->parent->color = BLACK;
				}

				w->right->color = BLACK;
				rb_left_rotate(T, x->parent);
				x = T->root;
			}
		} else {
			w = x->parent->left;

			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;

				rb_right_rotate(T, x->parent);
				w = x->parent->left;
			}

			if (w->left != NULL) {
				if (w->right != NULL && w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else if (w->left->color == BLACK) {
					if (w->right != NULL) {
						w->right->color = BLACK;
					}

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
	}

	if (x != NULL) {
		x->color = BLACK;
	}
}

void rb_delete(Tree * T, Node * z) {
	if (z == NULL) {
		return;
	}

	Node * y = z;
	Color y_original_color = y->color;
	Node * x;

	if (z->left == NULL) {
		x = z->right;
		rb_transplant(T, z, z->right);
	} else if (z->right == NULL) {
		x = z->left;
		rb_transplant(T, z, z->left);
	} else {
		y = rb_tree_minimum(z->right);
		if (y == NULL) {
			return;
		}

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

	// free(z)
}
