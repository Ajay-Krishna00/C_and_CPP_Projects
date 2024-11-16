#include <stdio.h>
struct poly
{
  int coeff;
  int expo;
};
void Insert(struct poly p[], int t)
{
  for (int i = 0; i < t; i++)
  {
    printf("Enter the coeff  ");
    scanf("%d", &p[i].coeff);
    printf("Enter the expo  ");
    scanf("%d", &p[i].expo);
  }
}
int polyAdd(struct poly result[], struct poly poly1[], struct poly poly2[], int t1, int t2)
{
  int t3 = 0;
  int i = 0; // Adjust t1 to be zero-indexed
  int j = 0; // Adjust t2 to be zero-indexed
  while (i < t1 && j < t2)
  {
    if (poly1[i].expo == poly2[j].expo)
    {
      result[t3].expo = poly1[i].expo;
      result[t3].coeff = poly1[i].coeff + poly2[j].coeff;
      j++;
      i++;
      t3++;
    }
    else if (poly1[i].expo < poly2[j].expo)
    {
      result[t3].expo = poly2[j].expo;
      result[t3].coeff = poly2[j].coeff;
      t3++;
      j++;
    }
    else if (poly1[i].expo > poly2[j].expo)
    {
      result[t3].expo = poly1[i].expo;
      result[t3].coeff = poly1[i].coeff;
      t3++;
      i++;
    }
  }
  while (j < t2)
  {
    result[t3].expo = poly2[j].expo;
    result[t3].coeff = poly2[j].coeff;
    t3++;
    j++;
  }
  while (i < t1)
  {
    result[t3].expo = poly1[i].expo;
    result[t3].coeff = poly1[i].coeff;
    t3++;
    i++;
  }
  return t3;
}
void sort(struct poly p[], int t)
{
  for (int i = 0; i < t - 1; i++)
  {
    for (int j = 0; j < t - i - 1; j++)
    {
      if (p[j].expo < p[j + 1].expo)
      {
        struct poly temp = p[j];
        p[j] = p[j + 1];
        p[j + 1] = temp;
      }
    }
  }
}
void Display(struct poly p[], int t)
{
  for (int i = 0; i < t - 1; i++)
    printf("%d(x^%d) + ", p[i].coeff, p[i].expo);
  printf("%d(x^%d)\n", p[t - 1].coeff, p[t - 1].expo);
}
void main()
{
  int t1, t2, t3;
  struct poly poly1[50], poly2[50], result[50];
  printf("Enter the no of terms in polynomial 1\n");
  scanf("%d", &t1);
  printf("Enter the no of terms in polynomial 2\n");
  scanf("%d", &t2);
  printf("Enter the terms in polynomial 1\n");
  Insert(poly1, t1);
  printf("Enter the terms in polynomial 2\n");
  Insert(poly2, t2);
  sort(poly1, t1);
  sort(poly2, t2);
  printf("The Entered Polynomial 1 is: ");
  Display(poly1, t1);
  printf("The Entered Polynomial 2 is: ");
  Display(poly2, t2);
  t3 = polyAdd(result, poly1, poly2, t1, t2);
  printf("The result is: ");
  Display(result, t3);
}