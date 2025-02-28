#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct
{
  int name; // Process name (1, 2, 3, ...)
  int AT;   // Arrival time
  int BT;   // Burst time
  int CT;   // Completion time
  int WT;   // waiting time
  int TAT;  // turn around time
  int processStarted;
  int remainingBT;
} Process;

struct Queue
{
  Process data;
  struct Queue *next;
};

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
  struct Queue *head = NULL;
  int TimeQuantum = 2;
  printf("Time Quantum=%d\n", TimeQuantum);
  // Define the processes
  Process processes[] = {
      {1, 0, 8}, // Arrival time = 0, Burst time = 8
      {2, 1, 1}, // Arrival time = 1, Burst time = 1
      {3, 2, 3}, // Arrival time = 2, Burst time = 3
      {4, 3, 2}, // Arrival time = 3, Burst time = 2
      {5, 4, 6}, // Arrival time = 4, Burst time = 6
  };
  int n = sizeof(processes) / sizeof(Process); // Number of processes

  sortAT(processes, n);
  for (int i = 0; i < n; i++)
  {
    processes[i].remainingBT = processes[i].BT;
    processes[i].processStarted = 0;
  }

  int currenttime = 0;
  int completedProcess = 0;

  while (completedProcess < n)
  {
    //for newly arrived processes which are not started yet
    for (int i = 0; i < n; i++)
    {
      if (processes[i].AT <= currenttime && processes[i].processStarted == 0)
      {
        struct Queue *newNode = (struct Queue *)malloc(sizeof(struct Queue));
        newNode->data = processes[i];
        newNode->next = NULL;

        if (head == NULL)
        {
          head = newNode;
        }
        else
        {
          struct Queue *ptr = head;
          while (ptr->next != NULL)
          {
            ptr = ptr->next;
          }
          ptr->next = newNode;
        }
        processes[i].processStarted = 1;
      }
    }
    if (head == NULL)
    {
      currenttime++;
      continue;
    }

    struct Queue *temp = head;
    Process currentProcess = temp->data;
    head = head->next;          // Dequeue
    free(temp);

    int execution_time = (currentProcess.remainingBT > TimeQuantum) ? TimeQuantum : currentProcess.remainingBT;
    currenttime += execution_time;
    currentProcess.remainingBT -= execution_time;    
    //for newly arrived processes which came while executing the current process
    for (int i = 0; i < n; i++)
    {
      if (processes[i].AT <= currenttime && processes[i].processStarted == 0)
      {
        struct Queue *newNode = (struct Queue *)malloc(sizeof(struct Queue));
        newNode->data = processes[i];
        newNode->next = NULL;

        if (head == NULL)
        {
          head = newNode;
        }
        else
        {
          struct Queue *ptr = head;
          while (ptr->next != NULL)
          {
            ptr = ptr->next;
          }
          ptr->next = newNode;
        }
        processes[i].processStarted = 1;
      }
    }
      
      if (currentProcess.remainingBT > 0)
      {
        struct Queue *newNode = (struct Queue *)malloc(sizeof(struct Queue));
        newNode->data = currentProcess;
        newNode->next = NULL;

        if (head == NULL)
        {
          head = newNode;
        }
        else
        {
          struct Queue *ptr = head;
          while (ptr->next != NULL)
          {
            ptr = ptr->next;
          }
          ptr->next = newNode;
        }
      }
      else
      {
        // Process has completed
        int i = currentProcess.name - 1;
        processes[i].CT = currenttime;
        processes[i].TAT = processes[i].CT - processes[i].AT;
        processes[i].WT = processes[i].TAT - processes[i].BT;
        completedProcess++;
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