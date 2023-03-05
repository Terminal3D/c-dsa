#include <stdio.h>


unsigned long peak(unsigned long nel,
                   int (*less)(unsigned long i, unsigned long j)) {
    if (nel == 1)
        return 0;
    if (less(1, 0))
        return 0;
    if (less(nel-2, nel-1))
        return --nel;
    unsigned long i = 1;
    while(i < nel - 1){
        if (!less(i, i-1) && !less(i, i+1))
            return i;
        ++i;
    }
}

int arr[7] = {1, 2, 3, 4, 5, 8, 7};

int less(unsigned long i, unsigned long j) {
    if (arr[i] < arr[j]) {
        return 1;
    }
    return 0;
}

int main() {
    unsigned long ans = peak(7, less);
    printf("%lu", ans);
    return 0;
}