#include <stdio.h>
#include <math.h>

#define N 3

int main()
{
    float a[N][N + 1] = {
        {5, 1, 8, 46},
        {4, -2, 0, 12},
        {6, 7, 4, 50}};
    float t;
    int i, j, k;

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            if (i != j)
            {
                t = a[i][j] / a[j][j];
                for (k = 0; k < N + 1; k++)
                {
                    a[i][k] = a[i][k] - a[j][k] * t;
                }
            }
        }
    }

    printf("diagonal matrix:-\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            printf("%9.4f ", a[i][j]);
        }
        printf("\n");
    }

    printf("solution:-\n");
    for (i = 0; i < N; i++)
    {
        printf("x[%3d]= %7.4f\n", i + 1, a[i][N] / a[i][i]);
    }
    return 0;
}