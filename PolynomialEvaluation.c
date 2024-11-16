#include <stdio.h>
#include<math.h>
struct poly
{
  int coeff;
  int expo;
  int val;
};
char ch[] = {'x', 'y', 'z'};
void Insert(struct poly p[], int t)
{
  for (int i = 0; i < t; i++)
  {
    printf("Enter the coeff of term %d  ",i+1);
    scanf("%d", &p[i].coeff);
    printf("Enter the expo of term %d  ", i + 1);
    scanf("%d", &p[i].expo);
    printf("Enter the value of %c  ",ch[i]);
    scanf("%d", &p[i].val);
  }
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
double polyEval(struct poly p[],int t)
{
  double single[20],res=0;
  for (int i = 0; i < t;i++)
  {
    single[i] = p[i].coeff*(pow(p[i].val,p[i].expo));
  }
  for (int i = 0; i < t;i++)
  {
    res+=single[i];
  }
  return res;
}
void Display(struct poly p[], int t)
{
  for (int i = 0; i < t - 1; i++)
    printf("%d(%d^%d) + ", p[i].coeff,p[i].val, p[i].expo);
  printf("%d(%d^%d)\n", p[t - 1].coeff, p[t-1].val, p[t - 1].expo);
}
void main()
{
  int t1;
  double result;
  struct poly poly1[50];
  printf("Enter the no of terms in polynomial\n");
  scanf("%d", &t1);
  printf("Enter the terms in polynomial\n");
  Insert(poly1, t1);
  sort(poly1, t1);
  printf("The Entered Polynomial is: ");
  Display(poly1, t1);
  result=polyEval(poly1, t1);
  printf("The result is: %lf",result);
}