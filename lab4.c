#include <stdio.h>
#include <stdlib.h>

#define MAX_ITERATIONS 100

void simplex(double **tableau, int rows, int cols)
{
    while (1)
    {
        int pivot_col = 0, pivot_row = 0;
        double min_positive = __DBL_MAX__;
        for (int i = 0; i < cols - 1; i++)
        {
            if (tableau[rows - 1][i] < 0 && tableau[rows - 1][i] < min_positive)
            {
                min_positive = tableau[rows - 1][i];
                pivot_col = i;
            }
        }

        if (pivot_col == 0)
            break;

        double min_ratio = __DBL_MAX__;
        for (int i = 0; i < rows - 1; i++)
        {
            if (tableau[i][pivot_col] > 0)
            {
                double ratio = tableau[i][cols - 1] / tableau[i][pivot_col];
                if (ratio < min_ratio)
                {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }

        pivot_on(tableau, pivot_row, pivot_col);

        print_tableau(tableau, rows, cols);
    }

    printf("Optimal solution found:\n");
    for (int i = 0; i < rows - 1; i++)
    {
        printf("x%d = %lf\n", i + 1, tableau[i][cols - 1]);
    }
    printf("Maximum value (z) = %lf\n", tableau[rows - 1][cols - 1]);
}

int main()
{

    double **tableau;
    int rows;
    int cols;

    simplex(tableau, rows, cols);

    for (int i = 0; i < rows; i++)
        free(tableau[i]);
    free(tableau);

    return 0;
}