#include<stdio.h>
void main()
{
	int r,c,arr[20][20],count=0;
	float ans;
	printf("Enter the no of rows: ");
	scanf("%d",&r);
	printf("Enter the no of column: ");
	scanf("%d",&c);
	printf("Enter the Elements of the matrix: ");
	for (int i=0;i<r;i++)
	{
		for (int j=0;j<c;j++)
		{
			scanf("%d",&arr[i][j]);
			if (arr[i][j]!=0)
			{
				count++;
			}
		}
	}
	printf("The matrix is: \n");
	for (int i=0;i<r;i++)
	{
		for (int j=0;j<c;j++)
		{
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	if (count!=0)
	{
		printf("The Representation is: \n");
		printf(" rows\t| column| value\n");
		for (int i=0;i<r;i++)
		{
			for (int j=0;j<c;j++)
			{
				if(arr[i][j]!=0)
				{
					printf(" %d\t| %d\t| %d\n",i,j,arr[i][j]);
				}
			}
		}
	}
	else 
	{
		printf("No non zero elements present ");
	}
	
}


