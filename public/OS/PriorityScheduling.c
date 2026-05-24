#include <stdio.h>

// Structure to represent a process
typedef struct
{
  int name; // Process name (1, 2, 3, ...)
  int priority; // Priority of the process
  int AT;   // Arrival time
  int BT;   // Burst time
  int CT;   // Completion time
  int WT;   // waiting time
  int TAT;  // turn around time

} Process;

void sortAT(Process processes[], int n)
{
  Process temp;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (processes[i].AT > processes[j].AT)
      {
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
    processes[i].CT = 0;
  }
}

int main()
{
  // Define the processes
  Process processes[] = {
      {1, 4, 0, 8}, // Arrival time = 0, Burst time = 8
      {2, 3, 1, 1}, // Arrival time = 1, Burst time = 1
      {3, 3, 2, 3}, // Arrival time = 2, Burst time = 3
      {4, 2, 3, 2}, // Arrival time = 3, Burst time = 2
      {5, 1, 4, 6},  // Arrival time = 4, Burst time = 6
  };
  int n = sizeof(processes) / sizeof(Process); // Number of processes

  sortAT(processes, n);

  int currenttime = 0;
  int completedProcess = 0;
  Process temp = processes[0];

  while (completedProcess < n)
  {
    for (int i = 0; i < n; i++)
    {
      if (processes[i].AT <= currenttime && processes[i].CT == 0)
      {
        if (processes[i].priority < temp.priority)
        {
          temp = processes[i];
        }
      }
    }
    int execution_time = temp.BT;

    currenttime += execution_time;
    temp.CT = currenttime;
    temp.TAT = temp.CT - temp.AT;
    temp.WT = temp.TAT - temp.BT;
    completedProcess++;
    for (int i = 0; i < n; i++)
    {
      if (processes[i].name == temp.name)
      {
        processes[i] = temp;
        temp.priority = 9999;
        break;
      }
    }
  }

  float avgWt = 0.0;
  float avgTat = 0.0;
  printf("Process  ArrivalTime BurstTime CompletedTime TurnaroundTime    WaitingTime\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d%10d%15d%10d%15d%20d\n", processes[i].name, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].WT);
    avgWt = avgWt + processes[i].WT;
    avgTat = avgTat + processes[i].TAT;
  }
  printf("Average Waiting Time=%f\n", avgWt / n);
  printf("Average turnaround Time=%f\n", avgTat / n);

  return 0;
}