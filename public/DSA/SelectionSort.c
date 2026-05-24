#include<stdio.h>
void selectionSort(int arr[],int n)
{
  for (int i = 0; i < n - 1;i++)
  {
    int min = i;
    for (int j = i + 1; j < n;j++)
    {
      if(arr[j]<arr[min])
        min = j;
    }
    if (min != i)
    {
      int temp = arr[i];
      arr[i] = arr[min];
      arr[min] = temp;
    }
  }
}
void main()
{
  int n,arr[50];
  printf("Enter the length of the array ");
  scanf("%d",&n);
  printf("Enter the elements of the array ");
  for (int i = 0; i < n;i++)
  {
    scanf("%d", &arr[i]);
  }
  selectionSort(arr, n);
  printf("the sorted array is: ");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
}