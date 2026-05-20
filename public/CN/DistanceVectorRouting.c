#include <stdio.h>

#define MAX 10
#define INF 999

void printTable(int dist[MAX][MAX], int n)
{
  int i, j;

  printf("\nDistance Table:\n");

  for (i = 0; i < n; i++)
  {
    printf("Router %d: ", i);

    for (j = 0; j < n; j++)
    {
      printf("%3d ", dist[i][j]);
    }

    printf("\n");
  }
}

int main()
{
  int n;
  int cost[MAX][MAX];
  int dist[MAX][MAX];

  int i, j, k;
  int updated;
  int iteration = 1;

  printf("Enter number of routers: ");
  scanf("%d", &n);

  printf("Enter cost matrix (use 999 for infinity):\n");

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      scanf("%d", &cost[i][j]);
      dist[i][j] = cost[i][j];
    }
  }

  printf("\nInitial Distance Table:\n");
  printTable(dist, n);

  // Distance Vector Algorithm
  do
  {
    updated = 0;

    printf("\n========== Iteration %d ==========\n", iteration);

    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        for (k = 0; k < n; k++)
        {
          if (dist[i][j] > cost[i][k] + dist[k][j])
          {
            printf("\nUpdate found:\n");
            printf("Router %d -> Router %d via Router %d\n", i, j, k);

            printf("Old Cost = %d\n", dist[i][j]);

            printf("New Cost = %d + %d = %d\n",
                  cost[i][k],
                  dist[k][j],
                  cost[i][k] + dist[k][j]);

            dist[i][j] = cost[i][k] + dist[k][j];

            updated = 1;
          }
        }
      }
    }

    printTable(dist, n);

    iteration++;

  } while (updated);

  printf("\nFinal Distance Tables:\n");
  printTable(dist, n);

  return 0;
}