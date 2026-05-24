#include <stdio.h>
#include <stdlib.h>
struct poly
{
  int coeff;
  int expo;
  struct poly *next;
};
struct poly *Insert(struct poly *p, int t)
{
  struct poly *ptr = p;
  for (int i = 0; i < t; i++)
  {
    struct poly *newN = (struct poly *)malloc(sizeof(struct poly));
    printf("Enter the coeff of term %d ", i + 1);
    scanf("%d", &newN->coeff);
    printf("Enter the expo of term %d  ", i + 1);
    scanf("%d", &newN->expo);
    newN->next = NULL;
    if (p == NULL)
    {
      p = newN;
      ptr = p;
    }
    else
    {
      while (ptr->next != NULL)
      {
        ptr = ptr->next;
      }
      ptr->next = newN;
    }
  }
  return p;
}
void Display(struct poly *p)
{
  struct poly *ptr = p;
  while (ptr->next != NULL)
  {
    printf("%d(x^%d) + ", ptr->coeff, ptr->expo);
    ptr = ptr->next;
  }
  printf("%d(x^%d) ", ptr->coeff, ptr->expo);
}
struct poly *AddTerm(struct poly *result, int coeff, int expo)
{
  struct poly *newN = (struct poly *)malloc(sizeof(struct poly));
  newN->coeff = coeff;
  newN->expo = expo;
  newN->next = NULL;

  if (result == NULL)
  {
    return newN;
  }

  struct poly *ptr = result, *prev = NULL;
  while (ptr != NULL && ptr->expo > expo)
  {
    prev = ptr;
    ptr = ptr->next;
  }

  if (ptr != NULL && ptr->expo == expo)
  {
    ptr->coeff += coeff;
    free(newN);
  }
  else
  {
    if (prev == NULL)
    {
      newN->next = result;
      result = newN;
    }
    else
    {
      prev->next = newN;
      newN->next = ptr;
    }
  }
  return result;
}

struct poly *Multiply(struct poly *p1, struct poly *p2)
{
  struct poly *result = NULL;
  struct poly *ptr1 = p1, *ptr2;

  while (ptr1 != NULL)
  {
    ptr2 = p2;
    while (ptr2 != NULL)
    {
      int coeff = ptr1->coeff * ptr2->coeff;
      int expo = ptr1->expo + ptr2->expo;
      result = AddTerm(result, coeff, expo);
      ptr2 = ptr2->next;
    }
    ptr1 = ptr1->next;
  }
  return result;
}
void main()
{
  int t1, t2, t3;
  struct poly *poly1 = NULL, *poly2 = NULL, *result = NULL;
  printf("Enter the no of terms in polynomial 1\n");
  scanf("%d", &t1);
  printf("Enter the no of terms in polynomial 2\n");
  scanf("%d", &t2);
  printf("Enter the terms in polynomial 1\n");
  poly1 = Insert(poly1, t1);
  printf("Enter the terms in polynomial 2\n");
  poly2 = Insert(poly2, t2);
  printf("The Entered Polynomial 1 is: ");
  Display(poly1);
  printf("\nThe Entered Polynomial 2 is: ");
  Display(poly2);
  printf("\nThe result is: ");
  result = Multiply(poly1, poly2);
  Display(result);
}