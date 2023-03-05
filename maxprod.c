//Не алгоритм Кадана. Рабочие имплементации в папках algo1 и algo2.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <float.h>

void max_prod(double* arr, int size) {
    double max_prod = -DBL_MAX;
    int l = 0, r = 0;
    for (int i = 0; i < size; i++) {
        double prod = 1;
        for (int j = i; j < size; j++) {
            prod *= arr[j];
            if (prod > max_prod) {
                max_prod = prod;
                l = i;
                r = j;
            }
        }
    }
    printf("%d %d\n", l, r);
}
double str_frac_to_num(const char* str) {
    char* p;
    double numerator = strtod(str, &p);
    if (*p != '/') {
        return numerator;
    }
    p++;
    double denominator = strtod(p, NULL);
    return numerator / denominator;
}

int main() {
    unsigned int n;
    scanf("%ui", &n);
    double frac[n];
    for (int i = 0; i < n; i++){
        char temp[15];
        scanf("%s", temp);
        frac[i] = str_frac_to_num(temp);
    }
    max_prod(frac, n);
    return 0;
}