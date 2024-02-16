#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ND 2
#define NS 2
#define N (ND + NS)
void init(float x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = 0;
    }
}

int main()
{
    int bas[NS];
    float a[NS][N + 1] = {
        {2, 1, 1, 0, 14}, // x1 + x2 + s1 = 14
        {4, 3, 0, 1, 28}  // 4x1 + 3x2 + s2 = 28
    };
    float c[N] = {-1, -1, 0, 0};
    float cb[NS] = {0}, th[NS] = {0};
    float x[ND] = {0};
    int i, j, k, ki, kj;
    float cj, z, t, b, min, max;

    for (i = 0; i < NS; i++)
        bas[i] = ND + i;

    do
    {
        max = 0;
        kj = -1;

        for (j = 0; j < N; j++)
        {
            cj = -c[j];
            for (i = 0; i < NS; i++)
            {
                cj += a[i][j] * cb[i];
            }
            if (cj > max)
            {
                max = cj;
                kj = j;
            }
        }

        if (kj < 0)
            break;

        min = 1e30; // large number
        ki = -1;
        for (i = 0; i < NS; i++)
        {
            if (a[i][kj] < 1e-5)
                continue;
            t = a[i][N] / a[i][kj];
            if (t < min)
            {
                min = t;
                ki = i;
            }
        }

        if (ki < 0)
        {
            printf("Unbounded solution\n");
            return 1;
        }

        cb[ki] = c[kj];
        bas[ki] = kj;

        t = a[ki][kj];
        for (j = 0; j <= N; j++)
            a[ki][j] /= t;
        for (i = 0; i < NS; i++)
        {
            if (i != ki)
            {
                t = a[i][kj];
                for (j = 0; j <= N; j++)
                    a[i][j] -= t * a[ki][j];
            }
        }
    } while (1);

    z = 0;
    for (i = 0; i < NS; i++)
    {
        if (bas[i] < ND)
            x[bas[i]] = a[i][N];
    }
    for (i = 0; i < ND; i++)
    {
        z += x[i] * -c[i];
    }

    for (i = 0; i < ND; i++)
        printf("x[%d] = %.2f\n", i + 1, x[i]);
    printf("Optimal value = %.2f\n", z);

    return 0;
}