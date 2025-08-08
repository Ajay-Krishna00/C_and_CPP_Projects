#include <stdio.h>
void main()
{
  int n, seek = 0;
  printf("Enter the no of process\n");
  scanf("%d", &n);
  int arr[n];
  printf("Enter the process\n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  int head;
  printf("Enter the current position of head\n");
  scanf("%d", &head);
  printf("Pro\tHead Mov\n");
  for (int i = 0; i < n; i++)
  {
    int max = arr[i] > head ? arr[i] : head;
    int min = arr[i] > head ? head : arr[i];
    seek += (max - min);
    head = arr[i];
    printf("%d\t%d\n", arr[i], max - min);
  }
  printf("Seek time: %d\n", seek);
}