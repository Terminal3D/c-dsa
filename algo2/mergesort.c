#include <stdio.h>
#include <stdlib.h>

struct stack{
    int l, r;
    int d;
    struct stack *pred;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    scanf("%d", &n);
    int array[n];
    for(int i = 0 ; i < n ; i++)
        scanf("%d", &array[i]);
    struct stack *Stack = malloc(sizeof (struct stack));
    Stack->l = 0;
    Stack->r = n - 1;
    Stack->d = 1;
    Stack->pred = NULL;
    while (Stack != NULL){
        int left = Stack->l, right = Stack->r;
        int d = Stack->d;
        struct stack *temp_s = Stack;
        Stack = Stack->pred;
        free(temp_s);
        if(d == 1){
            if(right - left + 1 <= 5){
                for(int i = left + 1 ; i <= right ; i++)
                    for(int j = i ;  j >= left + 1 && abs(array[j]) < abs(array[j - 1]); j--){
                        int temp = array[j];
                        array[j] = array[j - 1];
                        array[j - 1] = temp;
                    }
            }else{
                struct stack *new_Stack1_1 = malloc(sizeof (struct stack));
                struct stack *new_Stack2_1 = malloc(sizeof (struct stack));
                struct stack *new_Stack1_2 = malloc(sizeof (struct stack));
                struct stack *new_Stack2_2 = malloc(sizeof (struct stack));
                int mid = (left + right) / 2;
                new_Stack1_1->pred = Stack;
                new_Stack1_1->l = left;
                new_Stack1_1->r = mid - 1;
                new_Stack1_1->d = 2;
                Stack = new_Stack1_1;
                new_Stack2_1->pred = Stack;
                new_Stack2_1->l = mid;
                new_Stack2_1->r = right;
                new_Stack2_1->d = 2;
                Stack = new_Stack2_1;
                new_Stack1_2->pred = Stack;
                new_Stack1_2->l = left;
                new_Stack1_2->r = mid - 1;
                new_Stack1_2->d = 1;
                Stack = new_Stack1_2;
                new_Stack2_2->pred = Stack;
                new_Stack2_2->l = mid;
                new_Stack2_2->r = right;
                new_Stack2_2->d = 1;
                Stack = new_Stack2_2;
            }
        }else{
            int left2 = Stack->l;
            int mid = left;
            left = left2;
            struct stack *temp_s = Stack;
            Stack = Stack->pred;
            free(temp_s);
            int ind_l1 = left, ind_l2 = mid;
            int *temp_array = calloc(right - left + 1, sizeof(int));
            for(int i = 0 ; i < right - left + 1 ; i++){
                if(ind_l1 != mid && ind_l2 != right + 1){
                    if(abs(array[ind_l1]) <= abs(array[ind_l2]))
                        temp_array[i] = array[ind_l1++];
                    else
                        temp_array[i] = array[ind_l2++];
                }else{
                    if(ind_l1 == mid)
                        temp_array[i] = array[ind_l2++];
                    else
                        temp_array[i] = array[ind_l1++];
                }
            }
            for(int i = 0 ; i < right - left + 1; i++)
                array[i + left] = temp_array[i];
            free(temp_array);
        }
    }
    for(int i = 0 ; i < n ; i++)
        printf("%d ", array[i]);
    return 0;
}