#include <stdio.h>
void swap(int *a,int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i+1], &arr[high]);
  return (i + 1);
}
void quickSort(int arr[],int low,int high)
{
  if(low<high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
void main()
{
  int n, arr[50];
  printf("Enter the length of the array: ");
  scanf("%d", &n);
  printf("Enter the elements of the array\n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  quickSort(arr, 0, n - 1);
  printf("The sorted array is: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
}