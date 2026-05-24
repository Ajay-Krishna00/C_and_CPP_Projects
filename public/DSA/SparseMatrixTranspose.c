#include <stdio.h>

typedef struct
{
  int row;
  int col;
  int val;
} sparse;

void Display(sparse A[20], int Aterm)
{
  printf("| rows \t| col \t| val \t|\n");
  for (int i = 0; i < Aterm; i++)
  {
    printf("| %d \t| %d \t| %d \t|\n", A[i].row, A[i].col, A[i].val);
  }
}
void Transpose(sparse A[20], int Aterm, sparse T[20])
{
  for (int i = 0; i < Aterm; i++)
  {
    T[i].row = A[i].col;
    T[i].col = A[i].row;
    T[i].val = A[i].val;
  }
  printf("Transpose is:\n");
  Display(T, Aterm);
}

void main()
{
  sparse A[20], T[20];
  int Aterm;
  printf("Enter the no of rows in the tuple: ");
  scanf("%d", &Aterm);
  printf("Enter the Sparse Representation \n");
  printf("Enter the row, column and value for each non zero element in matrices \n");
  for (int i = 0; i < Aterm; i++)
  {
    scanf("%d %d %d", &A[i].row, &A[i].col, &A[i].val);
  }
  printf("Entered tuple is:\n");
  Display(A, Aterm);
  Transpose(A, Aterm, T);
}