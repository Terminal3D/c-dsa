#include <stdio.h>
#define True 1


int array[1000000];
int tree[4000000];
int n;

int peak(int i) {
    if (i == 0 && n > 1)
        return (array[i] > array[i + 1]);
    else if (i == 0 && n == 1)
        return 1;
    else if (i == (n - 1))
        return (array[i] > array[i - 1]);
    else
        return (array[i] > array[i - 1] && array[i] > array[i + 1]);
}

void buildTree(int i, int a, int b) {
    if (a == b)
        tree[i] = peak(a);
    else {
        int m = (a + b) / 2;
        buildTree(2 * i + 1, a, m);
        buildTree(2 * i + 2, m + 1, b);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

int query(int l, int r, int i, int a, int b) {
    if ((l == a) && (r == b))
        return tree[i];
    else {
        int m = (a + b) / 2;
        if (r <= m)
            return (query(l, r, 2 * i + 1, a, m));
        else if (l > m)
            return (query(l, r, 2 * i + 2, m + 1, b));
        else
            return (query(l, m, 2 * i + 1, a, m) +
                    query(m + 1, r, 2 * i + 2, m + 1, b));
    }
}

void update(int j, int i, int a, int b) {
    if (a == b)
        tree[i] = peak(j);
    else {
        int m = (a + b) / 2;
        if (j <= m)
            update(j, 2 * i + 1, a, m);
        else
            update(j, 2 * i + 2, m + 1, b);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
}

void take_peak() {
    int l, r;
    scanf("%i %i", &l, &r);
    printf("%i\n", query(l, r, 0, 0, n - 1));
}

void upd() {
    int i, v;
    scanf("%i %i", &i, &v);
    array[i] = v;
    update(i, 0, 0, n-1);
    if (i != 0)
        update(i - 1, 0, 0, n-1);
    if (i != (n-1))
        update(i + 1, 0, 0, n-1);
}

int main() {
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
        scanf("%i", &array[i]);
    buildTree(0, 0, n - 1);

    char op[5];
    while (True) {
        scanf("%s", op);
        if (op[0] == 'P')
            take_peak();
        else if (op[0] == 'U')
            upd();
        else
            break;
    }

    return 0;
}