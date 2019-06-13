#include "binary_search.h"

int binary_search(int x, int v[], int n) {
	int low = 0, high = n - 1;
	int middle;

	while (low <= high) {
		middle = (low + high) / 2;

		if (v[middle] > x) {
			high = middle - 1;
		} else if (v[middle] < x) {
			low = middle + 1;
		} else {
			return middle;
		}
	}

	return -1;
}
