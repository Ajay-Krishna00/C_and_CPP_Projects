#include <stdio.h>
void sort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
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
  sort(arr, n);
  int head, FH, SH;
  printf("Enter the current position of head\n");
  scanf("%d", &head);
  printf("Pro\tHead Mov\n");
  for (int i = 0; i < n; i++)
  {
    if (arr[i] > head)
    {
      // find n<head
      FH = i - 1;
      // find n>head
      SH = i;
      break;
    }
  }
  for (int i = FH; i >= 0; i--)
  {
    int max = arr[i] > head ? arr[i] : head;
    int min = arr[i] > head ? head : arr[i];
    seek += (max - min);
    head = arr[i];
    printf("%d\t%d\n", arr[i], max - min);
  }

  seek += (head - 0);
  printf("0\t%d\n", head);
  head = 0;

  for (int i = SH; i < n; i++)
  {
    int max = arr[i] > head ? arr[i] : head;
    int min = arr[i] > head ? head : arr[i];
    seek += (max - min);
    head = arr[i];
    printf("%d\t%d\n", arr[i], max - min);
  }
  printf("Seek time: %d\n", seek);
}