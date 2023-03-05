#include <stdio.h>
#include <stdlib.h>
int mas[1000001];
int t[4000004];
int mmax(int a, int b){
    if (a>b)
        return a;
    return b;
}
int mmin(int a, int b){
    if (a<b)
        return a;
    return b;
}
void build(int v, int tl, int tr){
    if (tl==tr){
        t[v]=mas[tl];
    }
    else{
        int m=(tl+tr)/2, v2=2*v;
        build(v2, tl, m);
        build(v2+1, m+1, tr);
        t[v]=mmax(t[v2], t[v2+1]);
    }
}
int fimax (int v, int tl, int tr, int l, int r){
    if (l>r)
        return 0;
    if (l==tl && r==tr)
        return t[v];
    int m=(tl+tr)/2, v2=2*v;
    if (l > mmin(r, m))
        return fimax(v2+1, m+1, tr, mmax(l, m+1), r);
    if (mmax(l, m+1) > r)
        return fimax(v2, tl, m, l, mmin(r, m));
    return mmax(fimax(v2, tl, m, l, mmin(r, m)), fimax(v2+1, m+1, tr, mmax(l, m+1), r));
}
void update(int v, int tl, int tr, int pos, int val){
    if (tl==tr)
        t[v]=val;
    else {
        int m=(tl+tr)/2, v2=2*v;
        if (pos<=m)
            update(v2, tl, m, pos, val);
        else
            update(v2+1, m+1, tr, pos, val);
        t[v]=mmax(t[v2], t[v2+1]);
    }
}
int main()
{
    int n, m, arg1, arg2;
    char s[5];
    scanf("%d", &n);
    for (int i=0; i<n; ++i){
        scanf("%d", &mas[i]);
    }
    scanf("%d", &m);
    build(1, 0, n-1);
    while (1!=0){
        scanf("%s %d %d", &s, &arg1, &arg2);
        if (s[0]=='M'){
            printf("%d\n", fimax(1, 0, n-1, arg1, arg2));
        }
        else {
            if (s[0]=='U')
                update(1, 0, n-1, arg1, arg2);
            else
                break;
        }
    }
    return 0;
}