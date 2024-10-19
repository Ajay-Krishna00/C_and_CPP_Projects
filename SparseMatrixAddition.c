#include<stdio.h>
struct sparseTerm
{
	int row;
	int col;
	int val;
};

int addSparce(struct sparseTerm A[],int Aterm,struct sparseTerm B[],int Bterm,struct sparseTerm C[])
{
	int i=0,j=0,k=0;
	while (i<Aterm && j<Bterm)
	{
		if (A[i].row==B[j].row && A[i].col==B[j].col )
		{
			C[k].row=A[i].row;
			C[k].col=B[j].col;
			C[k].val=A[i].val + B[j].val;
			i++;j++;k++;
		}
		else if(A[i].row<B[j].row || (A[i].row == B[j].row && A[i].col < B[j].col))
		{
			C[k]=A[i];
			i++;k++;
			
		}
		else
		{
			C[k]=B[j];
			k++;j++;
		}
		
	}
	while(i<Aterm)
	{
		C[k]=A[i];
		i++;k++;
		
	}
	while(j<Bterm)
	{
		C[k]=B[j];
		k++;j++;
	}
	return k;
}
void main()
{
	struct sparseTerm A[20],B[20],C[20];
	int Aterm,Bterm,Cterm,r,c;
	printf("Enter the no. of the rows and  columns of matrices: \n");
	scanf("%d%d",&r,&c);
	printf("Enter the no. non zero elements in matrices 1: \n");
	scanf("%d",&Aterm);
	printf("Enter the no. non zero elements in matrices 2: \n");
	scanf("%d",&Bterm);
	printf("Enter the rows columns and values for each non zero element in matrices 1: \n");
	for (int i=0;i<Aterm;i++)
	{
		scanf("%d %d %d",&A[i].row,&A[i].col,&A[i].val);
	}
	printf("Enter the rows columns and values for each non zero element in matrices 2: \n");
	for (int i=0;i<Bterm;i++)
	{
		scanf("%d %d %d",&B[i].row,&B[i].col,&B[i].val);
	}
	Cterm=addSparce(A,Aterm,B,Bterm,C);
	printf("The Added matrix is \n");
	printf("row\t|col\t|val\n");
	for (int i=0;i<Cterm;i++)
	{
		printf("%d\t| %d\t| %d\t\n",C[i].row,C[i].col,C[i].val);
	}
}
