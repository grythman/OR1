#include <stdio.h>

#define MAX_VERTICES 10
#define MAX_ARROWS (MAX_VERTICES - 1)

struct Graph
{
    int vertices;
    int arrows[MAX_ARROWS][2];
    int loads[MAX_VERTICES];
};

int isValidBasicSolution(struct Graph *g)
{
    int in[MAX_VERTICES] = {0}, out[MAX_VERTICES] = {0};
    int connected[MAX_VERTICES] = {0};
    int totalArrows = 0, i, j;

    for (i = 0; i < g->vertices - 1; i++)
    {
        int src = g->arrows[i][0];
        int dest = g->arrows[i][1];

        out[src]++;
        in[dest]++;
        totalArrows++;

        connected[src] = connected[dest] = 1;
    }

    for (i = 0; i < g->vertices; i++)
    {
        if (!((in[i] == 0 && out[i] == 1) || (in[i] == 1 && out[i] == 0)))
            return 0;
    }

    if (totalArrows != g->vertices - 1)
        return 0;

    for (i = 0; i < g->vertices; i++)
    {
        for (j = 0; j < g->vertices; j++)
        {
            if (i != j && connected[i] && !connected[j])
                return 0;
        }
    }

    return 1;
}

void addArrow(struct Graph *g, int src, int dest)
{
    static int arrowIndex = 0;
    if (arrowIndex < MAX_ARROWS)
    {
        g->arrows[arrowIndex][0] = src;
        g->arrows[arrowIndex][1] = dest;
        arrowIndex++;
    }
}

int main()
{
    struct Graph g;
    g.vertices = 4;

    addArrow(&g, 0, 1);
    addArrow(&g, 1, 2);
    addArrow(&g, 2, 3);

    if (isValidBasicSolution(&g))
    {
        printf("load distribution in the network is a basic solution.\n");
    }
    else
    {
        printf("The load distribution does not meet the basic conditions.\n");
    }

    return 0;
}