#include "quicksort.h"

void quicksort(int * A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

int partition(int * A, int p, int r) {
    int x = A[r]; // pivot
    int i = p - 1;

    int j;
    for (j = p; j < r; ++j) {
        if (A[j] <= x) {
            ++i;
            int aux = A[i];
            A[i] = A[j];
            A[j] = aux;
        }
    }

    int aux = A[i + 1];
    A[i + 1] = A[r];
    A[r] = aux;

    return i + 1;
}
