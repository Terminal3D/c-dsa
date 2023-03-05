#include <stdio.h>
#include <stdlib.h>

void calc(char* fib_array, unsigned long long x){
    unsigned long long array[100];
    array[0] = 1;
    array[1] = 1;
    int j = 2;
    while(array[j - 1] <= x){
        array[j] = array[j-1] + array[j-2];
        j++;
    }
    j -= 2;
    int l = 0;
    while (l <= j){
        if(x >= array[j - l]){
            fib_array[j - l] = 1;
            x -= array[j - l];
        }
        l++;
    }
    for(; l >= 2; l--) {
        printf("%i", fib_array[l - 1]);
    }
    return;
}

void printarray(char* array2, int k){
    for(; k >= 2; k--){
        printf("%i", array2[k - 1]);
    }
}

int main()
{
    unsigned long long x;
    scanf("%llu", &x);
    char* result = calloc(100, sizeof(unsigned long long));

    if (x == 0 || x == 1){
        printf("%llu", x);
        free(result);
        return 0;
    }

    calc(result, x);

    free(result);
    return 0;
}