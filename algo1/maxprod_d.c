#include <stdio.h>
#include <stdlib.h>

void find_max_product(const double* values, const int size, int* start_index, int* end_index) {
    double max_prod = values[0];
    double max = values[0];
    int s = 0;

    for (int i = 1; i < size; i++) {
        if (values[i] > max * values[i]) {
            max = values[i];
            s = i;
        } else {
            max *= values[i];
        }
        if (max > max_prod) {
            max_prod = max;
            *start_index = s;
            *end_index = i;
        }
    }
}

void scan_fraction(double* num, double* denom) {
    char separator;
    if (scanf("%lf %c %lf", num, &separator, denom) != 3 || separator != '/') {
        printf("Invalid input");
        exit(1);
    }
}

int main() {
    int num_fractions;
    scanf("%i", &num_fractions);
    double values[num_fractions];
    for (int i = 0; i < num_fractions; i++) {
        double num, denom;
        scan_fraction(&num, &denom);
        values[i] = num / denom;
    }

    int start_index = 0, end_index = 0;
    find_max_product(values, num_fractions, &start_index, &end_index);
    printf("%d %d\n", start_index, end_index);

    return 0;
}
