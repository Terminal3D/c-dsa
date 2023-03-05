#include <stdio.h>
#include <stdlib.h>

struct Date {
    int Day, Month, Year;
};

void radixSort(struct Date *dates, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        max = max > dates[i].Year ? max : dates[i].Year;
    }

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int output[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(dates[i].Year / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(dates[i].Year / exp) % 10] - 1] = dates[i];
            count[(dates[i].Year / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            dates[i] = output[i];
        }
    }
}

int main() {

    int n;
    scanf("%d", &n);

    struct Date dates[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }

    radixSort(dates, n);

    for (int i = 0; i < n; i++) {
        printf("%04d %02d %02d ", dates[i].Year, dates[i].Month, dates[i].Day);
    }

    return 0;
}
