#include <stdio.h>

void findMaxProd(double* arr, int size) {
    double max_so_far = arr[0];
    double curr_max = arr[0];
    int start = 0, end = 0;
    int s = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i] > curr_max * arr[i]) {
            curr_max = arr[i];
            s = i;
        } else {
            curr_max *= arr[i];
        }
        if (curr_max > max_so_far) {
            max_so_far = curr_max;
            start = s;
            end = i;
        }
    }
    printf("%d %d", start, end);
}

int main() {
    int numerator, denominator, n;
    char slash;
    scanf("%i", &n);
    double arr[n];
    int i = 0;
    while (i < n) {
        scanf("%i%c%i", &numerator, &slash, &denominator);
        arr[i] = (double)numerator / (double)denominator;
        i++;
    }
    findMaxProd(arr, n);
}