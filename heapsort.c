#include <stdio.h>
#include <stdlib.h>



void hsort(void *base, size_t nel, size_t width, int (*compare)(const void *a, const void *b)) {
// build heap
    for (int i = (nel - 2) / 2; i >= 0; i--) {
        siftDown(base, i, nel - 1, width, compare);
    }
// sort heap
    for (int i = nel - 1; i > 0; i--) {
        swap(base, base + i * width, width);
        siftDown(base, 0, i - 1, width, compare);
    }
}
