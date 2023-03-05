#include <stdio.h>

unsigned long long mod_mult(unsigned long long a, unsigned long long b, unsigned long long m){
    unsigned long long res;
    char bm[64];
    int i = 0;
    while (b>0){
        bm[i] = (char)(b % 2);
        i++;
        b /=2;
    }
    res = a * bm[--i];
    while (i > 0){
        res = (((res % m) * 2) % m) + (a % m) * (bm[--i] % m);
    }
    return (res % m);
}


int main(){
    unsigned long long a, b, m, i;
    scanf("%llu %llu %llu", &a, &b, &m);
    i = mod_mult(a, b, m);
    printf("%llu", i);

    return 0;
}