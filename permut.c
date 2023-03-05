#include <stdio.h>

char arr_compare(long *a, long *b) {
    char i = 0, j = 0, c1 = 0, c2 = 0;
    long cur_elem;
    while (i < 8) {
        cur_elem = a[i];
        while (j < 8) {
            if (a[j] == cur_elem)
                c1++;
            if (b[j] == cur_elem)
                c2++;
            j++;
        }
        if (c1 == c2) {
            c1 = 0;
            c2 = 0;
            j = 0;
        } else return 0;
        i++;
    }
    return 1;
}
void scanArray(long *arr){
    int i = 0;
    while (i < 8){
        scanf("%li", &arr[i]);
        i++;
    }
}
int main() {
    long a[8], b[8];
    scanArray(a);
    scanArray(b);
    if (arr_compare(a, b))
        printf("yes");
    else
        printf("no");
    return 0;
};