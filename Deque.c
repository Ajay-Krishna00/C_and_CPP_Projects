#include <stdio.h>

int front = -1;
int rear = -1;
int size = 0;

void EnqueueFront(int ans, int deque[], int n)
{
  if (size == n)
  {
    printf("Queue is full");
    return;
  }
  if (front == -1 && rear == -1)
  {
    front = 0;
    rear = 0;
  }
  if (front == 0)
  {
    front = n - 1;
  }
  else
    front--;
  deque[front] = ans;
  size++;
}
void EnqueueRear(int ans, int deque[], int n)
{
  if (size == n)
  {
    printf("Queue is full");
    return;
  }
  if (front == -1 && rear == -1)
  {
    front = 0;
    rear = 0;
  }
  if (rear == n - 1)
  {
    rear = 0;
  }
  else
    rear++;
  deque[rear] = ans;
  size++;
}
void DequeueFront( int deque[], int n)
{
  if (front == -1 && rear == -1)
  {
    printf("Queue is Empty");
    return;
  }
  if (front == rear)
  {
    front = -1;
    rear = -1;
    return;
  }
  if (front == n - 1)
  {
    front = 0;
  }
  else front++;
  size--;
}
void DequeueRear( int deque[], int n)
{
  if (front == -1 && rear == -1)
  {
    printf("Queue is Empty");
    return;
  }
  if (front == rear)
  {
    front = -1;
    rear = -1;
    return;
  }
  if (rear == 0)
  {
    rear = n - 1;
  }
  else rear--;
  size--;
}
void Display(int deque[], int n)
{
  printf("Deque: ");
  int count = size;
  int i = front;
  while (count--)
  {
    printf("%d  ", deque[i]);
    i = (i + 1) % n;
  }
}

void main()
{
  int inp, ans, deque[50], n;
  printf("Enter the size of the deque: ");
  scanf("%d", &n);
  while(1)
  {
    printf("\nEnter 1 for Enqueue at front\n2 for Dequeue at front\n3 for Enqueue at rear\n4 for Dequeue at rear\n5 to exit\n");
    scanf("%d", &inp);
    switch (inp)
    {
    case 1:
      printf("\nEnter the element: ");
      scanf("%d", &ans);
      EnqueueFront(ans, deque, n);
      Display(deque,n);
      break;
    case 2:
      DequeueFront( deque, n);
      Display(deque,n);
      break;
    case 3:
      printf("\nEnter the element: ");
      scanf("%d", &ans);
      EnqueueRear(ans, deque, n);
      Display(deque,n);
      break;
    case 4:
      DequeueRear( deque, n);
      Display(deque,n);
      break;
    case 5:
      return;
    default:
      printf("Invalid input");
      break;
    }}
}