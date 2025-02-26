#include <stdio.h>

// Structure to represent a process
typedef struct
{
  int name;       // Process name (1, 2, 3, ...)
  int AT;    // Arrival time
  int BT;      // Burst time
  int CT; // Completion time
  int WT;    // waiting time
  int TAT; // turn around time

} Process;

void sortAT(Process processes[],int n){
  Process temp;
  for (int i = 0; i < n-1;i++){
    for (int j = i + 1; j < n;j++){
      if(processes[i].AT > processes[j].AT){
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
}

    int main()
{
  // Define the processes
  Process processes[] = {
    {2, 1, 1}, // Arrival time = 1, Burst time = 1
    {4, 3, 2}, // Arrival time = 3, Burst time = 2
    {5, 4, 6}, // Arrival time = 4, Burst time = 6
    {3, 2, 3}, // Arrival time = 2, Burst time = 3
    {1, 0, 8}, // Arrival time = 0, Burst time = 8
  };
  int n = sizeof(processes) / sizeof(Process); // Number of processes
  sortAT(processes, n);
  int currenttime = 0;

  for (int i = 0; i < n; i++)
  {
    // Check if the process has arrived and is not yet completed
    int execution_time = processes[i].BT;

    currenttime += execution_time;

    processes[i].CT = currenttime;
    processes[i].TAT = processes[i].CT - processes[i].AT;
    processes[i].WT = processes[i].TAT - processes[i].BT;
  }

  float avgWt = 0.0;
  float avgTat = 0.0;
  printf("Process  ArrivalTime CompletedTime BurstTime TurnaroundTime    WaitingTime\n");
  for (int i = 0; i < n; i++)
  {
    printf("P%d%10d%10d%10d%15d%20d\n", processes[i].name, processes[i].AT, processes[i].CT, processes[i].BT, processes[i].TAT, processes[i].WT);
    avgWt = avgWt + processes[i].WT;
    avgTat = avgTat + processes[i].TAT;
  }
  printf("Average Waiting Time=%f\n", avgWt / n);
  printf("Average turnaround Time=%f\n", avgTat / n);

  return 0;
}