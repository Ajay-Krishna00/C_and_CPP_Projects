#include <stdio.h>
#include<stdlib.h>

struct Node
{
  int coeff;
  int expo;
  struct Node *next;
};

struct Node *createNode( int i)
{
  struct Node *new = (struct Node *)malloc(sizeof(struct Node));
  printf("Enter the coefficient of %dth term: ", i + 1);
  scanf("%d", &new->coeff);
  printf("Enter the exponent of %dth term: ", i + 1);
  scanf("%d", &new->expo);
  new->next = NULL;
  return new;
}

struct Node *Insertion(struct Node *p, int i)
{
  struct Node *ptr = p,*new = createNode(i);
  if (p == NULL)
  {
    return new; 
  }
  while (ptr->next != NULL)
  {
    ptr=ptr->next;
  }
  ptr->next = new;
  return p;
}
struct Node *Insert(struct Node *result,int co,int e)
{
  struct Node *ptr = result;
  struct Node *new = (struct Node *)malloc(sizeof(struct Node));
  new->coeff=co;
  new->expo = e;
  new->next = NULL;
  if (result == NULL)
  {
    return new;
  }
  while (ptr->next != NULL)
  {
    ptr=ptr->next;
  }
  ptr->next = new;
  return result;
}

struct Node *Add(struct Node *p1, struct Node *p2)
{
  struct Node *result=NULL;
  while(p1!=NULL && p2!=NULL)
  {
    if(p1->expo==p2->expo)
    {
      result=Insert(result,p1->coeff+p2->coeff,p2->expo);
      p1 = p1->next;
      p2 = p2->next;
    }
    else if (p1->expo > p2->expo)
    {
      result=Insert(result,p1->coeff,p1->expo);
      p1 = p1->next;
    }
    else
    {
      result=Insert(result, p2->coeff, p2->expo);
      p2 = p2->next;
    }
  }
  while(p1!=NULL)
  {
    result=Insert(result, p1->coeff, p1->expo);
    p1 = p1->next;
  }
  while (p2 != NULL)
  {
    result=Insert(result, p2->coeff, p2->expo);
    p2 = p2->next;
  }
  return result;
}

void Display(struct Node *p)
{
  struct Node *ptr = p;
  if (p == NULL)
  {
    printf("0\n");
    return;
  }
  while (ptr->next != NULL)
  {
    printf("%dx^%d+", ptr->coeff, ptr->expo);
    ptr = ptr->next;
  }
  printf("%dx^%d\n", ptr->coeff, ptr->expo);
}

void main()
{
  struct Node *p1 = NULL, *p2 = NULL, *result=NULL;
  int t1, t2;
  printf("Enter the no of terms of the 1st polynomial: ");
  scanf("%d", &t1);
  printf("Enter the no of terms of the 2nd polynomial: ");
  scanf("%d", &t2);
  printf("Enter the values of the 1st polynomial\n");
  for (int i = 0; i < t1;i++)
  {
    p1 = Insertion(p1, i);
  }
  printf("Enter the values of the 2nd polynomial\n");
  for (int i = 0; i < t2;i++)
  {
    p2 = Insertion(p2, i);
  }
  printf("Entered values of the 1st polynomial is:\t");
  Display(p1);
  printf("Entered values of the 2nd polynomial is:\t");
  Display(p2);
  printf("The Result is:\t");
  result = Add(p1, p2);
  Display(result);
}