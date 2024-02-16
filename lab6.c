#include <stdio.h>
#include <stdlib.h>

#define M 4 
#define N 4 

void northWestCorner(int supply[], int demand[], int cost[M][N], int allocation[M][N]) {
    int i = 0, j = 0;

    // Initialize the allocation array
    for (int u = 0; u < M; u++) {
        for (int v = 0; v < N; v++) {
            allocation[u][v] = 0;
        }
    }

    while (i < M && j < N) {
        if (supply[i] < demand[j]) {
            // supply less than demand
            allocation[i][j] = supply[i];
            demand[j] -= supply[i];
            supply[i] = 0;
            i++;
        } else {
            // demand  less than or equal to supply
            allocation[i][j] = demand[j];
            supply[i] -= demand[j];
            demand[j] = 0;
            j++;
        }
    }
}

int calculateCost(int supply[], int demand[], int cost[M][N], int allocation[M][N]) {
    int totalCost = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            totalCost += allocation[i][j] * cost[i][j];
        }
    }
    return totalCost;
}

void printAllocation(int allocation[M][N]) {
    printf("Allocation Matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int supply[M] = {20, 30, 25, 25}; 
    int demand[N] = {30, 20, 30, 20}; 
    int cost[M][N] = { 
        {2, 3, 1, 4},
        {3, 2, 4, 1},
        {5, 2, 3, 4},
        {2, 1, 2, 3}
    };
    
    int allocation[M][N];

    northWestCorner(supply, demand, cost, allocation);

    int totalCost = calculateCost(supply, demand, cost, allocation);

    printAllocation(allocation);
    printf("Total cost transportation: %d\n", totalCost);

    return 0;
}