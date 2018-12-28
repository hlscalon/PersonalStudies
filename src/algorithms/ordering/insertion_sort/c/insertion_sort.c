#include "insertion_sort.h"

void insertion_sort(int * A, int length) {
	int j;
	for (j = 1; j < length; ++j) {
		int key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key) {
			A[i + 1] = A[i];
			--i;
		}
		A[i + 1] = key;
	}
}
