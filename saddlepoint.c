#include <stdio.h>

#define L 10

char findSaddlePoint(int mat[L][L], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        int min_row = mat[i][0], col_ind = 0;
        for (int j = 1; j < m; j++)
        {
            if (min_row > mat[i][j])
            {
                min_row = mat[i][j];
                col_ind = j;
            }
        }

        int k;
        for (k = 0; k < i; k++)

            if (min_row < mat[k][col_ind])
                break;

        if (k == n)
        {
            printf("%d %d",i, col_ind);
            return 1;
        }
    }

    return 0;
}

// Driver code
int main()
{
    int n, m;
    scanf("%i %i", &n, &m);
    int arr[L][L];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%i", &arr[i][j]);
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }
    if (findSaddlePoint(arr, n, m) == 0)
        printf("none");
    return 0;
}