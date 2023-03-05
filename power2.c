#include <stdio.h>

void single_counter(int n, int *arr, int index, long sum, int *ans) {

    for (; index < n; index++) {
        if ((sum+arr[index] != 0) && (sum + arr[index] & (sum + arr[index] - 1)) == 0)
            (*ans)++;
        single_counter(n, arr, index + 1, sum + arr[index], ans);
    }
}

int power_counter(int n, int *arr) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        single_counter(n, arr, i + 1, arr[i], &counter);
    }
    return counter;
}


void scanArray(int *arr, int n) {
    int i = 0;
    while (i < n) {
        scanf("%i", &arr[i]);
        i++;
    }
}

int main() {
    int a[24];
    int n;
    scanf("%i", &n);
    scanArray(a, n);
    int t = power_counter(n, a);
    printf("%i", t);
    return 0;
}