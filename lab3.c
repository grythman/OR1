#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void printTbl(float tableau[MAX_ROWS][MAX_COLS], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", tableau[i][j]);
        }
        printf("\n");
    }
}

void initTbl(float tableau[MAX_ROWS][MAX_COLS], int m, int n) {
    // Initialize the tableau with coefficients of the objective function and constraints
    // Replace this with your problem coefficients
    float c[MAX_COLS] = {3, 2};  // Objective function coefficients
    float A[MAX_ROWS][MAX_COLS] = {
        {2, 3},
        {1, 2}
    };  // Constraint coefficients
    float b[MAX_ROWS] = {6, 4};  // Right-hand side values
    
    // Copy the objective function coefficients to the tableau
    for (int j = 0; j < n; j++) {
        tableau[0][j] = c[j];
    }
    
    // Copy the constraint coefficients and right-hand side values to the tableau
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            tableau[i][j] = A[i-1][j];
        }
        tableau[i][n] = b[i-1];
    }
}

void basicAndFreeUnknowns(float tableau[MAX_ROWS][MAX_COLS], int m, int n) {
    // Identify basic and free unknowns
    int mU[MAX_COLS] = {0};  // Array to store whether a variable is a main unknown (1) or not (0)
    
    // Check each column to see if it forms part of the identity matrix in the tableau
    for (int j = 0; j < n; j++) {
        int cnt1 = 0;  // Count of ones in the column
        int rInd = -1;  // Index of the row with the one
        
        // Iterate over each row in the column
        for (int i = 1; i <= m; i++) {
            if (tableau[i][j] == 1) {
                cnt1++;
                rInd = i;
            } else if (tableau[i][j] != 0) {
                cnt1 = 0;  // Reset count if non-zero value found
                break;
            }
        }
        
        // If exactly one one found in the column, mark the corresponding variable as a main unknown
        if (cnt1 == 1) {
            mU[j] = 1;
            printf("Variable x%d is a main unknown.\n", j + 1);
        }
    }
    
    // Identify free unknowns based on variables that are not main unknowns
    printf("Free unknowns: ");
    for (int j = 0; j < n; j++) {
        if (!mU[j]) {
            printf("x%d ", j + 1);
        }
    }
    printf("\n");
}

int main() {
    int m = 2;  // Number of constraints
    int n = 2;  // Number of decision variables
    
    float tableau[MAX_ROWS][MAX_COLS];
    
    // Initialize the tableau
    initTbl(tableau, m, n);
    
    // Print the initial tableau
    printf("Initial simplex tableau:\n");
    printTbl(tableau, m + 1, n + 1);
    
    // Identify main and free unknowns
    basicAndFreeUnknowns(tableau, m, n);
    
    return 0;
}
