#include<stdio.h>
void heapSort(int arr[],int n)
{
  for (int i = n / 2 - 1; i >=0;i--)
    heapify(arr, n, i);
  for (int i = n - 1; i > 0;i--)
    {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
    }
}
void main()
{
  int n, arr[50];
  printf("Enter the length of the array ");
  scanf("%d", &n);
  printf("Enter the elements of the array ");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  heapSort(arr, n);
  printf("the sorted array is: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
}