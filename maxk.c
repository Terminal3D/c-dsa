#include <stdio.h>

long max(long a, long b){
    if (a > b)
        return a;
    else
        return b;
}




int main(int argc, char **argv)
{
    long n, k;
    long i = 0;
    scanf("%li", &n);
    long a[n];
    while (i < n){
        scanf("%li", &a[i]);
        i++;
    }
    scanf("%li", &k);
    long j = 0;
    long sum = 0;
    while (j < k){
        sum += a[j];
        j++;
    }
    long long cSum = sum;
    while (j < n){
        cSum += a[j] - a[j - k];
        sum = max(sum, cSum);
        j++;
    }
    printf("%li", sum);
    return 0;
}
