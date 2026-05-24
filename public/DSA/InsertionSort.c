#include<stdio.h>
void insertionSort(int arr[],int n)
{
  for (int i = 1; i < n;i++)
  {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0&&arr[j]>key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
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
  insertionSort(arr, n);
  printf("the sorted array is: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
}