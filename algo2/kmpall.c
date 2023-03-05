#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int KMP(const char* word,const char* mask){
    int len_mask = (int) strlen(mask);
    int len_word = (int) strlen(word);
    int* pi = calloc(len_mask, sizeof(int));

    int j = 0;
    int i = 1;

    while (i < len_mask){
        if(mask[i] == mask[j]){
            pi[i] = j + 1;
            i++;
            j++;
        }
        else{
            if(j == 0){
                pi[i] = 0;
                i++;
            }
            else{
                j = pi[j - 1];
            }
        }
    }

    int res = 0;

    int k = 0;
    int l = 0;

    while (k < len_word) {

        if(word[k] == mask[l]){
            k++;
            l++;
            if(l == len_mask){
                res++;
                printf("%d ",k - l);
            }
        } else{
            if (l == 0){
                k++;
                if(k == len_word) {
                    free(pi);
                    return res;
                }
            }
            else
                l = pi[l - 1];
        }
    }
    free(pi);
    return res;
}


int main(int argc, char const *argv[])
{
    KMP(argv[2],argv[1]);
    return 0;
}