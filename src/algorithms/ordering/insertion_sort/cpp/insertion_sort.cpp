#include "insertion_sort.hpp"

void insertion_sort(std::vector<int> & A) {
    const int length = A.size();
    for (int j = 1; j < length; ++j) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            --i;
        }
        A[i + 1] = key;
    }
}
