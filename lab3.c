#include <stdio.h>

#define N 10
#define M 10

void printTbl(float tableau[N][M], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", tableau[i][j]);
        }
        printf("\n");
    }
}

void initTbl(float tableau[N][M], int m, int n) {
    float c[M] = {3, 2}; 
    float A[N][M] = {
        {2, 3},
        {1, 2}
    };  
    float b[N] = {6, 4};  

    for (int j = 0; j < n; j++) {
        tableau[0][j] = c[j];
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            tableau[i][j] = A[i-1][j];
        }
        tableau[i][n] = b[i-1];
    }
}

void basicAndFreeUnknowns(float tableau[N][M], int m, int n) {
    int mU[M] = {0};
    
    for (int j = 0; j < n; j++) {
        int cnt1 = 0; 
        int rInd = -1;  
        
        for (int i = 1; i <= m; i++) {
            if (tableau[i][j] == 1) {
                cnt1++;
                rInd = i;
            } else if (tableau[i][j] != 0) {
                cnt1 = 0;
                break;
            }
        }
        
        if (cnt1 == 1) {
            mU[j] = 1;
            printf("Variable x%d is a main unknown.\n", j + 1);
        }
    }
    
    printf("Free unknowns: ");
    for (int j = 0; j < n; j++) {
        if (!mU[j]) {
            printf("x%d ", j + 1);
        }
    }
    printf("\n");
}

int main() {
    int m = 2;  
    int n = 2; 
    
    float tableau[N][M];
    
    initTbl(tableau, m, n);
    
    printf("Initial simplex tableau:\n");
    printTbl(tableau, m + 1, n + 1);
    
    basicAndFreeUnknowns(tableau, m, n);
    
    return 0;
}
