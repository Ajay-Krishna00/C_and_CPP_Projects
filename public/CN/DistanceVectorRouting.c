#include <stdio.h>

#define MAX 10
#define INF 999

int main()
{
  int n;
  int cost[MAX][MAX];
  int dist[MAX][MAX];
  int i, j, k;
  int updated;

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

  // Distance Vector Algorithm (Bellman-Ford style)
  do
  {
    updated = 0;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        for (k = 0; k < n; k++)
        {
          if (dist[i][j] > cost[i][k] + dist[k][j])
          {
            dist[i][j] = cost[i][k] + dist[k][j];
            updated = 1;
          }
        }
      }
    }
  } while (updated);

  printf("\nFinal Distance Tables:\n");
  for (i = 0; i < n; i++)
  {
    printf("Router %d: ", i);
    for (j = 0; j < n; j++)
    {
      printf("%d ", dist[i][j]);
    }
    printf("\n");
  }

  return 0;
}
