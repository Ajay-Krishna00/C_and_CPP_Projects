#include<stdio.h>
int main(){
int m1,n1,m2,n2,choice;
printf("Enter What you want to do\n1 for Matrix addition\n2 for Transpose\n3 for Sum of Diagonals\n4 for Matrix multiplicaton\n ");
scanf("%d",&choice);
printf("Enter the no of rows and column of matrix 1\n");
scanf("%d%d",&m1,&n1);
int arr[m1][n1],i,j,sum=0;
printf("Enter the elements of the matrix\n");
for(i=0;i<m1;i++)
	for (j=0;j<n1;j++)
	{
		scanf("%d",&arr[i][j]);
	}
printf("the Entered matrix is\n");
for(i=0;i<m1;i++)
	for (j=0;j<n1;j++)
	{
		printf("%d",arr[i][j]);
		if(j==n1-1){printf("\n");}
	}
if (choice==2)
	{
		printf("The Transpose is\n");
		for(i=0;i<m1;i++)
		for (j=0;j<n1;j++)
		{
			printf("%d",arr[j][i]);
			if(j==n1-1){printf("\n");}
		}
	}
else if(choice==3)
	{
		if (m1!=n1){printf("Enter a square matrix!\n");}
		else
		{
		
		for (i=0;i<m1;i++)
			{
				sum+=arr[i][i];
			}
		printf("The Sum of Diagonal elements is%d\n",sum);
		}
	}
	

else if(choice==1)
{	
	printf("Enter the no. of rows and columns of matrix 2\n ");
	scanf("%d%d",&m2,&n2);
	int arr2[m2][n2];
	printf("Enter the elements of matrix 2\n ");
	for(i=0;i<m2;i++)
		for (j=0;j<n2;j++)
		{
			scanf("%d",&arr2[i][j]);
		}
	printf("the Entered matrix is\n");
	for(i=0;i<m2;i++)
		for (j=0;j<n2;j++)
		{
			printf("%d",arr2[i][j]);
			if(j==n2-1){printf("\n");}
		}
	if(choice==1)
	{	if(m2!=m1 || n2!=n1){printf("Enter matrix with same order");}
		else
		{for(i=0;i<m2;i++)
			for (j=0;j<n2;j++)
			{
				arr[i][j] += arr[i][j];
			}
		printf("The added matrix is \n");
		for(i=0;i<m2;i++)
			for (j=0;j<n2;j++)
			{
				printf("%d",arr[i][j]);
			if(j==n2-1){printf("\n");}
			}
		}
	}
}

return 0;
}