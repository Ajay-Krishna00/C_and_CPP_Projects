#include <stdio.h>
#include <stdlib.h>

int pageno = 0;

struct frames
{
  int data;
  struct frames *next;
};

struct frames *createNode(int d)
{
  struct frames *new = (struct frames *)malloc(sizeof(struct frames));
  new->data = d;
  new->next = NULL;
  return new;
}

void Enqueue(struct frames **head, int data)
{
  struct frames *ptr = *head;
  if (*head == NULL)
  {
    *head = createNode(data);
    return;
  }
  while (ptr->next != NULL)
  {
    ptr = ptr->next;
  }
  ptr->next = createNode(data);
}
struct frames *Dequeue(struct frames *head)
{
  if (head != NULL)
  {
    return head = head->next;
  }
  else
    return head;
}

void printFrames(struct frames *head, int pages[])
{
  struct frames *ptr = head;
  printf("%3d  ", pages[pageno]);
  while (ptr != NULL)
  {
    printf("  %d", ptr->data);
    ptr = ptr->next;
  }
  pageno++;
  printf("\n");
}

int pageInFrame(struct frames *head, int page)
{
  struct frames *ptr = head;
  if (head == NULL)
    return 0;
  while (ptr != NULL)
  {
    if (ptr->data == page)
      return 1;
    ptr = ptr->next;
  }
  return 0;
}

void main()
{
  int n, f, hit = 0, pageFault = 0;
  // printf("Enter the number of frames: ");
  // scanf("%d", &f);
  // printf("Enter the number of pages: ");
  // scanf("%d", &n);
  // int frames[f], pages[n];
  // printf("Enter the page reference string: ");
  // for(i = 0; i < n; i++){
  //   scanf("%d", &pages[i]);
  // }

  // sample values
  int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
  n = 15;
  f = 3;
  int count[n]=0;
  struct frames *head = NULL;
  printf("page  frame\n");
  for (int i = 0; i < n; i++)
  {
    if (pageInFrame(head, pages[i]) != 0)
    {
      hit++;
      printf("%3d    <", pages[pageno]);
      for (int j = 0; j < f; j++)
        printf("--");
      pageno++;
      count[i]++;
      printf("\n");
      continue;
    }
    if (i < f)
    {
      Enqueue(&head, pages[i]);
      printFrames(head, pages);
      pageFault++;
    }
    else
    {
      for (int j = 0; j < f; j++)
      {
        head = Dequeue(head);
      }
      for (int j = 0; j < f; j++)
      {
        Enqueue(&head, pages[i - j]);
      }
      printFrames(head, pages);
      pageFault++;
    }
  }
  printf("Page Fault: %d\n", pageFault);
  printf("Page Hit: %d\n", hit);
  float hitRatio = (float)hit / (pageFault + hit);
  printf("HitRatio: %.3f\n", hitRatio);
}