#include <stdio.h>

#define MAX 10
#define INF 999

void printDistances(int dist[], int visited[], int n)
{
  int i;

  printf("\nNode\tDistance\tVisited\n");
  for (i = 0; i < n; i++)
  {
    printf("%d\t%d\t\t%d\n", i, dist[i], visited[i]);
  }
}

int minDistance(int dist[], int visited[], int n)
{
  int min = INF, minIndex = -1;
  int i;

  for (i = 0; i < n; i++)
  {
    if (!visited[i] && dist[i] < min)
    {
      min = dist[i];
      minIndex = i;
    }
  }

  return minIndex;
}

int main()
{
  int n, source;
  int cost[MAX][MAX];
  int dist[MAX];
  int visited[MAX];
  int i, j, u;

  printf("Enter number of routers: ");
  scanf("%d", &n);

  printf("Enter cost matrix (use 999 for infinity):\n");
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      scanf("%d", &cost[i][j]);
    }
  }

  printf("Enter source router: ");
  scanf("%d", &source);

  // Initialize
  for (i = 0; i < n; i++)
  {
    dist[i] = cost[source][i];
    visited[i] = 0;
  }

  dist[source] = 0;
  visited[source] = 1;

  printf("\nInitial State:\n");
  printDistances(dist, visited, n);

  // Dijkstra Algorithm
  for (i = 1; i < n; i++)
  {
    u = minDistance(dist, visited, n);

    if (u == -1)
      break;

    visited[u] = 1;

    printf("\nSelected Router %d (minimum distance)\n", u);

    for (j = 0; j < n; j++)
    {
      if (!visited[j] && dist[j] > dist[u] + cost[u][j])
      {
        printf("\nUpdating Router %d:\n", j);
        printf("Old Distance = %d\n", dist[j]);
        printf("New Distance = %d + %d = %d\n",dist[u], cost[u][j], dist[u] + cost[u][j]);

        dist[j] = dist[u] + cost[u][j];
      }
    }

    printDistances(dist, visited, n);
  }

  printf("\nFinal Shortest Paths from Router %d:\n", source);
  for (i = 0; i < n; i++)
  {
    printf("Router %d -> Router %d = %d\n", source, i, dist[i]);
  }

  return 0;
}