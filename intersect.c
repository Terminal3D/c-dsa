#include <stdio.h>
unsigned long scanner(int size){
    int i = 0;
    int element;
    unsigned long res = 0;
    do{
        scanf("%i", &element);
        res = (res | (1 << element));
        i++;
    } while(i < size);
    return res;
}

int main(){
    int size_a, size_b;
    scanf("%i", &size_a);
    unsigned long a=0, b=0;
    if (size_a != 0)
        a = scanner(size_a);

    scanf("%i", &size_b);
    if (size_b != 0)
        b = scanner(size_b);
    a = a & b;
    for (int i = 0; i < 32; i++){
        if ((a | (1 << i)) == a)
            printf("%i ", i);

    }
    return 0;
}