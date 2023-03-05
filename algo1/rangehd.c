#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define True 1

typedef struct {
    int letters[26];
} tree_el;

char array[1000000];
char new_str[1000000];
tree_el tree[4000000];

int n;

void is_hyperdrome(int* arr) {
    int odd_count = 0;
    for (int i = 0; i < 26; i++)
        if (arr[i] % 2 != 0)
            odd_count++;
    if (odd_count > 1)
        printf("NO\n");
    else
        printf("YES\n");



}

void buildTree(int i, int a, int b) {
    if (a == b)
        (tree[i].letters[array[a] - 'a']++);
    else {
        int m = (a + b) / 2;
        buildTree(2 * i + 1, a, m);
        buildTree(2 * i + 2, m + 1, b);
        for (int j = 0; j < 26; j++) {
            tree[i].letters[j] = tree[2 * i + 1].letters[j] +
                                 tree[2 * i + 2].letters[j];
        }
    }
}

int* query(int l, int r, int i, int a, int b) {
    if ((l == a) && (r == b))
        return (tree[i].letters);
    else {
        int m = (a + b) / 2;
        if (r <= m)
            return (query(l, r, 2 * i + 1, a, m));
        else if (l > m)
            return (query(l, r, 2 * i + 2, m + 1, b));
        else {
            int* left =
            query(l, m, 2 * i + 1, a, m);
            int* right = query(m + 1, r, 2 * i + 2, m + 1, b);

            for (int j = 0; j < 26; j++)
                left[j] += right[j];
            return left;
        }
    }
}

void update(int j, int i, int a, int b) {
    if (a == b) {
        (tree[i].letters[array[a] - 'a']++);
        (tree[i].letters[array[j] - 'a']--);
    }
    else {
        int m = (a + b) / 2;
        if (j <= m)
            update(j, 2 * i + 1, a, m);
        else
            update(j, 2 * i + 2, m + 1, b);
        for (int k = 0; i < 26; i++) {
            tree[k].letters[array[a] - 'a'] = tree[2 * k + 1].letters[array[a] - 'a'] +
                                              tree[2 * k + 2].letters[array[a] - 'a'];
        }
    }
}

void take_hd() {
    int l, r;
    scanf("%i %i", &l, &r);
    int* arr = query(l, r, 0, 0, n - 1);
    is_hyperdrome(arr);
    memset(arr, 0, sizeof(int));
}

void upd() {
    int i;
    int j = 0;
    scanf("%i", &i);
    gets(new_str);
    while (new_str[j] != 0) {
        array[i] = new_str[j];
        update(i, 0, 0, n - 1);
        if (i != 0)
            update(i - 1, 0, 0, n - 1);
        if (i != (n - 1))
            update(i + 1, 0, 0, n - 1);
        i++;
        j++;
    }
}

int main() {
    gets(array);
    n = (int)strlen(array);
    buildTree(0, 0, n - 1);
    char op[5];
    while (True) {
        scanf("%s", op);
        if (op[0] == 'H')
            take_hd();
        else if (op[0] == 'U')
            upd();
        else
            break;
    }

    return 0;
}