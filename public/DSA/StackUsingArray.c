#include <stdio.h>
#include <stdlib.h>
int top = -1;
void push(int r, int s, int arr[])
{
  if (top == s - 1)
  {
    printf("Stack is full!");
  }
  else
  {
    top++;
    arr[top] = r;
  }
}
int pop(int arr[])
{
  int r;
  if (top == -1)
  {
    printf("Stack is empty!");
    return -1;
  }
  else
  {
    r = arr[top];
    if (top == 0)
      top = -1;
    else
      top--;
    return r;
  }
}
int peek(int arr[])
{
  if (top == -1)
  {
    printf("Stack is empty!");
  }
  else
  {
    return arr[top];
  }
}
int size()
{
  return top + 1;
}
void main()
{

  int inp, res, s, arr[50];
  printf("Enter the size of the array: ");
  scanf("%d", &s);
  while (1)
  {
    printf("\nEnter 1 for push\n 2 for pop\n 3 for peek\n 4 for size\n 5 for exit\n");
    scanf("%d", &inp);
    switch (inp)
    {
    case 1:
      printf("Enter the element to push: ");
      scanf("%d", &res);
      push(res, s, arr);
      break;
    case 2:
      res = pop(arr);
      if (res != -1)
        printf("The removed element is : %d", res);
      break;
    case 3:
      res = peek(arr);
      printf("The element at top is : %d", res);
      break;
    case 4:
      res = size(arr);
      printf("The size is : %d", res);
      break;
    case 5:
      exit(0);
    default:
      printf("Invalid input");
    }
  }
}