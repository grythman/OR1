#include <stdio.h>
#include <stdlib.h>

#define M 10 // Assuming a maximum matrix size of 10x10

// Jordan's Transformation
void J1sttran(double matrix[][M], int rows, int cols) {
    double identity[M][M] = {0};

    // Init unit matrix (identity matrix)
    for (int i = 0; i < rows; i++) {
        identity[i][i] = 1;
    }

    for (int i = 0; i < rows; i++) {
        // Find the pivot
        double pivot = matrix[i][i];
        if (pivot == 0) {
            // Find non-zero pivot and swap rows
            int k = i + 1;
            while (k < rows && matrix[k][i] == 0) k++;
            if (k < rows) {
                for (int j = 0; j < cols; j++) {
                    double temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;

                    temp = identity[i][j];
                    identity[i][j] = identity[k][j];
                    identity[k][j] = temp;
                }
                pivot = matrix[i][i]; // Update pivot
            }
        }

        for (int j = 0; j < cols; j++) {
            matrix[i][j] /= pivot;
            identity[i][j] /= pivot;
        }

        // reduced row echelon form
        for (int k = 0; k < rows; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < cols; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    identity[k][j] -= factor * identity[i][j];
                }
            }
        }
    }

    // Copy identity matrix to matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = identity[i][j];
        }
    }
}

int rankOfMatrix(double matrix[][M], int rows, int cols)
{
    int rank = 0;
    for (int row = 0; row < rows; ++row)
    {
        int allZeros = 1;
        for (int col = 0; col < cols; ++col)
        {
            if (matrix[row][col] != 0)
            {
                allZeros = 0;
                break;
            }
        }
        if (!allZeros)
        {
            ++rank;
        }
    }
    return rank;
}

void printMatrix(double matrix[][M], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%.3f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    double matrix[M][M] = {
        {1, -2, 3},
        {-1, 1, 2},
        {2, -1, -1}};
    int rows = 3, cols = 3;

    printf("Original Matrix:\n");
    printMatrix(matrix, rows, cols);

    J1sttran(matrix, rows, cols);

    printf("\nInverse Matrix:\n");
    printMatrix(matrix, rows, cols);

    printf("\nRank: %d\n", rankOfMatrix(matrix, rows, cols));

    return 0;
}