#include <stdio.h>

struct poly
{
  int exp;
  int coeff;
};

void Display(struct poly p[], int t)
{
  for (int i = 0; i < t - 1; i++)
    printf("%d(x^%d)+", p[i].coeff, p[i].exp);
  printf("%d(x^%d)", p[t - 1].coeff, p[t - 1].exp);
}

void AddPoly(struct poly p1[], struct poly p2[], int t1, int t2)
{
  struct poly p3[10];
  int i = 0, j = 0, k = 0;
  while (i < t1 && j < t2)
  {
    if (p1[i].exp == p2[j].exp)
    {
      p3[k].coeff = p1[i].coeff + p2[j].coeff;
      p3[k].exp = p1[i].exp;
      i++;
      j++;
      k++;
    }
    else if (p1[i].exp > p2[j].exp)
    {
      p3[k].coeff = p1[i].coeff;
      p3[k].exp = p1[i].exp;
      i++;
      k++;
    }
    else
    {
      p3[k].coeff = p1[j].coeff;
      p3[k].exp = p1[j].exp;
      j++;
      k++;
    }
  }
  while (i < t1)
  {
    p3[k].coeff = p1[i].coeff;
    p3[k].exp = p1[i].exp;
    i++;
    k++;
  }
  while (j < t2)
  {
    p3[k].coeff = p2[j].coeff;
    p3[k].exp = p2[j].exp;
    j++;
    k++;
  }
  printf("\nThe sum is:");
  Display(p3, k);
}

void main()
{
  struct poly p1[10], p2[10];
  int t1, t2;
  printf("Enter the no of terms of the first polynomial: ");
  scanf("%d", &t1);
  for (int i = 0; i < t1; i++)
  {
    printf("Enter the coefficient of %d th term: ", i + 1);
    scanf("%d", &p1[i].coeff);
    printf("Enter the exponent of %d th term: ", i + 1);
    scanf("%d", &p1[i].exp);
  }
  Display(p1, t1);
  printf("\nEnter the no of terms of the second polynomial: ");
  scanf("%d", &t2);
  for (int i = 0; i < t2; i++)
  {
    printf("Enter the coefficient of %d th term: ", i + 1);
    scanf("%d", &p2[i].coeff);
    printf("Enter the exponent of %d th term: ", i + 1);
    scanf("%d", &p2[i].exp);
  }
  Display(p2, t2);
  AddPoly(p1, p2, t1, t2);
}
