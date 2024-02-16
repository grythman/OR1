#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ND 2
#define NS 2
#define N (ND + NS)
#define N1 (NS * (N + 1))

void init(float x[], int n)
{
    for (int i = 0; i < n; i++)
    {
        x[i] = 0;
    }
}

int main()
{
    int i, j, k, ki, kj, bas[NS];
    float a[NS][N + 1], c[N], cb[NS], th[NS];
    float x[ND], cj, z, t, b, min, max;

    // Initializing the arrays to zero
    init(c, N);
    init(cb, NS);
    init(th, NS);
    init(x, ND);

    for (i = 0; i < NS; i++)
        init(a[i], N + 1);

    // Set coefficients for slack variables equal to one
    for (i = 0; i < NS; i++)
        a[i][i + ND] = 1.0;

    // Put the stack variables in the basis
    for (i = 0; i < NS; i++)
        bas[i] = ND + i;

    // Get the constraints and objective function
    printf("Enter the constraints\n");
    for (i = 0; i < NS; i++)
    {
        for (j = 0; j <= ND; j++)
        { // Equal to ND since we need ND + slack variables
            scanf("%f", &a[i][j]);
        }
    }

    printf("Enter the objective function\n");
    for (j = 0; j < ND; j++)
    {
        scanf("%f", &c[j]);
    }

    // Main simplex algorithm starts here
    while (1)
    {
        max = 0;
        kj = 0;

        for (j = 0; j < N; j++)
        {
            z = 0;
            for (i = 0; i < NS; i++)
                z += cb[i] * a[i][j];
            cj = c[j] - z;
            if (cj > max)
            {
                max = cj;
                kj = j;
            }
        }

        // Optimality test
        if (max <= 0)
            break;

        // Prepare for ratio test
        max = 0;
        for (i = 0; i < NS; i++)
            if (a[i][kj] != 0)
            {
                th[i] = a[i][N] / a[i][kj];
                if (th[i] > max)
                    max = th[i];
            }

        // Check for unbounded solution
        if (max <= 0)
        {
            printf("Unbounded solution\n");
            return 1;
        }

        // Identifying the outgoing variable
        min = max;
        ki = 0;
        for (i = 0; i < NS; i++)
            if ((th[i] < min) && (th[i] != 0))
            {
                min = th[i];
                ki = i;
            }

        // Pivot operation
        t = a[ki][kj];
        for (j = 0; j < N + 1; j++)
            a[ki][j] /= t;

        for (i = 0; i < NS; i++)
            if (i != ki)
            {
                b = a[i][kj];
                for (k = 0; k < N + 1; k++)
                    a[i][k] -= a[ki][k] * b;
            }
        cb[ki] = c[kj];
        bas[ki] = kj;
    }

    // Calculate the optimal value
    for (i = 0; i < NS; i++)
        if ((bas[i] >= 0) && (bas[i] < ND))
            x[bas[i]] = a[i][N];

    z = 0;
    for (i = 0; i < ND; i++)
        z += c[i] * x[i];

    for (i = 0; i < ND; i++)
        printf("x[%d]= %.2f\n", i + 1, x[i]);
    printf("Optimal value= %.2f\n", z);

    return 0;
}