#include <stdio.h>
#define P 5
#define R 3

void PrintMatrix(int a[][R], int pro[])
{
  for (int i = 0; i < P; i++)
  {
    printf("P%d ", pro[i]);
    for (int j = 0; j < R; j++)
    {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}

void ResNeed(int alloc[][R], int max[][R], int need[][R])
{
  for (int i = 0; i < P; i++)
  {
    for (int j = 0; j < R; j++)
    {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }
}

void Allocate(int process[], int alloc[][R], int max[][R], int avail[])
{
  int finished = 0;
  int processFinish[P];
  int need[P][R];
  printf("Res Needed\n");
  ResNeed(alloc, max, need);
  PrintMatrix(need, process);
  while (finished != P)
  {
    int progressMade = 0;
    for (int i = 0; i < P; i++)
    {
      if (processFinish[i] != 1)
      {
        int True = 0;
        for (int j = 0; j < R; j++)
        {
          if (need[i][j] <= avail[j])
          {
            True++;
          }
        }
        if (True == R)
        {
          printf("\nAvailable resource: ");
          for (int j = 0; j < R; j++)
          {
            printf("%d ", avail[j]);
            avail[j] += alloc[i][j];
          }
          printf("\nProcess P%d can be allocated the resource: ", process[i]);
          for (int j = 0; j < R; j++)
          {
            printf("%d ", need[i][j]);
          }
          finished++;
          processFinish[i] = 1;
          progressMade = 1;
        }
      }
    }
    if (progressMade == 0){
      printf("\nSystem is in a deadlock state!\n");
      break;
    }
  }
}

void main()
{
  int process[] = {0, 1, 2, 3, 4};
  int available[] = {3, 3, 2};
  int alloc[][R] = {
      {0, 1, 0},
      {2, 0, 0},
      {3, 0, 2},
      {2, 1, 1},
      {0, 0, 2},
  };
  int max[][R] = {
      {7, 5, 3},
      {3, 2, 2},
      {9, 0, 2},
      {2, 2, 2},
      {4, 3, 3},
  };
  printf("Res Allocated\n");
  PrintMatrix(alloc, process);
  printf("Maximum Res Needed\n");
  PrintMatrix(max, process);
  Allocate(process, alloc, max, available);
}