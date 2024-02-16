#include <stdio.h>
#include <stdlib.h>

#define M 10 

// Jordan's Transformation
void J1sttran(double a[][M], int r, int c) {
    double id[M][M] = {0};

    // Init unit mat (identity mat)
    for (int i = 0; i < r; i++) {
        id[i][i] = 1;
    }

    for (int i = 0; i < r; i++) {
        double pivot = a[i][i];
        if (pivot == 0) {
            int k = i + 1;
            while (k < r && a[k][i] == 0) k++;
            if (k < r) {
                for (int j = 0; j < c; j++) {
                    double t = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = t;

                    t = id[i][j];
                    id[i][j] = id[k][j];
                    id[k][j] = t;
                }
                pivot = a[i][i]; 
            }
        }

        for (int j = 0; j < c; j++) {
            a[i][j] /= pivot;
            id[i][j] /= pivot;
        }

        for (int k = 0; k < r; k++) {
            if (k != i) {
                double factor = a[k][i];
                for (int j = 0; j < c; j++) {
                    a[k][j] -= factor * a[i][j];
                    id[k][j] -= factor * id[i][j];
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            a[i][j] = id[i][j];
        }
    }
}

int rankM(double a[][M], int r, int c)
{
    int rank = 0;
    for (int r = 0; r < r; ++r)
    {
        int z = 1;
        for (int c = 0; c < c; ++c)
        {
            if (a[r][c] != 0)
            {
                z = 0;
                break;
            }
        }
        if (!z)
        {
            ++rank;
        }
    }
    return rank;
}

void printMatrix(double a[][M], int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%.3f\t", a[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    double a[M][M] = {
        {1, -2, 3},
        {-1, 1, 2},
        {2, -1, -1}};
    int r = 3, c = 3;

    printf("Original Matrix:\n");
    printMatrix(a, r, c);

    J1sttran(a, r, c);

    printf("\nInvere Matrix:\n");
    printMatrix(a, r, c);

    printf("\nRank: %d\n", rankM(a, r, c));

    return 0;
}