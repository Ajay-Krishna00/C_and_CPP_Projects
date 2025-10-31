#include <stdio.h>

struct process
{
  int id;
  int AT;
  int BT;
  int CT;
  int TAT;
  int WT;
  int rem;
};

int main()
{
  struct process pro[20];
  int n, tq;
  printf("\nEnter the no of process: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    pro[i].id = i + 1;
    printf("\nEnter the AT of process %d: ", i + 1);
    scanf("%d", &pro[i].AT);
    printf("\nEnter the BT of process %d: ", i + 1);
    scanf("%d", &pro[i].BT);
    pro[i].rem = pro[i].BT;
  }
  printf("\nEnter the Time Quantum: ");
  scanf("%d", &tq);

  printf("\nGantt Chart");
  printf("\n------------------------------------------------------------------------------------------\n");
  printf("| 0 |");

  int currTime = 0, completed = 0;
  float totalTAT = 0, totalWT = 0;

  while (completed < n)
  {
    int doneinthiscycle = 0;
    for (int i = 0; i < n; i++)
    {
      if (pro[i].AT <= currTime && pro[i].rem > 0)
      {
        doneinthiscycle++;
        int execTime = (pro[i].rem > tq) ? tq : pro[i].rem;
        pro[i].rem -= execTime;
        currTime += execTime;
        printf(" P%d | %d |", pro[i].id, currTime);

        if (pro[i].rem == 0)
        {
          pro[i].CT = currTime;
          pro[i].TAT = pro[i].CT - pro[i].AT;
          pro[i].WT = pro[i].TAT - pro[i].BT;
          totalTAT += pro[i].TAT;
          totalWT += pro[i].WT;
          completed++;
        }
      }
    }
    if (doneinthiscycle == 0)
    {
      currTime++;
    }
  }
  printf("\n------------------------------------------------------------------------------------------\n");
  printf("%8s %10s %10s %10s %10s %10s\n", "Pro", "AT", "BT", "CT", "TAT", "WT");
  for (int i = 0; i < n; i++)
  {
    printf("%8d %10d %10d %10d %10d %10d\n", pro[i].id, pro[i].AT, pro[i].BT, pro[i].CT, pro[i].TAT, pro[i].WT);
  }
  printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
  printf("\nAverage Waiting Time    = %.2f\n", totalWT / n);

  return 0;
}