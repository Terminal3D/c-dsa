#include <stdio.h>

int my_abs(int x) {
    return x < 0 ? -x : x;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int array[1000000];
int tree[4000000];

void buildTree(int i, int a, int b) {
    if (a == b)
        tree[i] = array[a];
    else {
        int m = (a + b) / 2;
        buildTree(2 * i + 1, a, m);
        buildTree(2 * i + 2, m + 1, b);
        tree[i] = gcd(tree[2 * i + 1], tree[2 * i + 2]);
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
            return query(l, m, 2 * i + 1, a, m) +
                   query(m + 1, r, 2 * i + 2, m + 1, b);
    }
}

int main() {
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; i++)
        scanf("%i", &array[i]);
    buildTree(0, 0, n - 1);
    int m;
    scanf("%i", &m);
    int l,r;
    for (int i = 0; i < m; i++) {
        scanf("%i %i", &l, &r),
        printf("%i\n", query(l, r, 0, 0, n-1));
    }
    return 0;
}