#include <stdio.h>
#include <stdlib.h>

#define MAX_ITERATIONS 100

void simplex(double **tableau, int rows, int cols) {
    while (1) {
        int pivot_col = 0, pivot_row = 0;
        double min_positive = __DBL_MAX__;
        // Find pivot column (most negative value in the bottom row, excluding last column)
        for (int i = 0; i < cols - 1; i++) {
            if (tableau[rows - 1][i] < 0 && tableau[rows - 1][i] < min_positive) {
                min_positive = tableau[rows - 1][i];
                pivot_col = i;
            }
        }
        
        // If no negative value found, optimal reached
        if (pivot_col == 0) break;
        
        // Find the pivot row
        double min_ratio = __DBL_MAX__;
        for (int i = 0; i < rows - 1; i++) {
            if (tableau[i][pivot_col] > 0) {
                double ratio = tableau[i][cols - 1] / tableau[i][pivot_col];
                if (ratio < min_ratio) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        
        // Now we have a pivot element at tableau[pivot_row][pivot_col]
        // Perform operations to make it the only non-zero value in its column
        pivot_on(tableau, pivot_row, pivot_col);
        
        // Print updated tableau, for illustration
        print_tableau(tableau, rows, cols);
    }

    // Solution is now in the last column of the tableau.
    printf("Optimal solution found:\n");
    for (int i = 0; i < rows - 1; i++) {
        printf("x%d = %lf\n", i+1, tableau[i][cols - 1]);
    }
    printf("Maximum value (z) = %lf\n", tableau[rows - 1][cols - 1]);
}

int main() {
    /* You must define and initialize the tableau here. */
    /* `rows` should be the number of constraints + 1, `cols` should be the number of variables + constraints + 2. */
  
    double **tableau; // Suppose already initialized with proper constraint equations.
    int rows; // m + 1 where m is the number of constraints
    int cols; // n + m + 1 where n is the number of variables
  
    // Perform the Simplex algorithm.
    simplex(tableau, rows, cols);

    // Free the tableau memory.
    for (int i = 0; i < rows; i++) free(tableau[i]);
    free(tableau);

    return 0;
}