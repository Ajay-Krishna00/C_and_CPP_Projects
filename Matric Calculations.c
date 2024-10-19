/*This program will do Matric addition, Matrix multiplication, Transpose of a matrix and sum of diagonals of the matrix*/
#include<stdio.h>
#include<stdlib.h>
int main(){
int m1,n1,m2,n2,choice;

do
{
printf("Enter What you want to do\n1 for Matrix addition\n2 for Transpose\n3 for Sum of Diagonals\n4 for Matrix multiplicaton\n ");
scanf("%d",&choice);

//if entered wrong input
	if(choice<1 || choice>4)
	{printf("Enter correct number\n\n");}	
}while (choice<1 || choice>4);

printf("Enter the no of rows and column of matrix 1\n");
scanf("%d\t%d",&m1,&n1);
int i,j,sum=0;

//int arr[m1][n1];
//Dynamic Allocaton
int **arr=(int **) malloc(m1 * sizeof(int *));
for(i=0; i<m1; i++ )
{
	arr[i] =(int *) malloc(n1 * sizeof(int ));
}


printf("Enter the elements of the matrix\n");
for(i=0;i<m1;i++)
	for (j=0;j<n1;j++)
	{
		scanf("\t%d",&arr[i][j]);
	}
printf("the Entered matrix is\n");
for(i=0;i<m1;i++)
	for (j=0;j<n1;j++)
	{
		printf("%d\t",arr[i][j]);
		if(j==n1-1){printf("\n");}
	}

//to find Transpose of the Matrix
if (choice==2)
	{
		printf("The Transpose is\n");
		for(i=0;i<m1;i++)
		for (j=0;j<n1;j++)
		{
			printf("%d\t",arr[j][i]);
			if(j==n1-1){printf("\n");}
		}
	}
//to find Sum of the Diagonals of the Matrix
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
	

else if(choice==1 || choice==4)
{	
	printf("Enter the no. of rows and columns of matrix 2\n ");
	scanf("%d%d",&m2,&n2);
	//int arr2[m2][n2];
	int **arr2=(int **) malloc(m2 * sizeof(int *));
	for(i=0; i<m2; i++ )
	{
		arr2[i] =(int *) malloc(n2 * sizeof(int ));
	}
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
			printf("%d\t",arr2[i][j]);
			if(j==n2-1){printf("\n");}
		}

	//to do Matrix Addition
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
				printf("%d\t",arr[i][j]);
			if(j==n2-1){printf("\n");}
			}
		}
	}

	//to do Matrix Multiplication
	if(choice==4)
	{
		if (n1!=m2)
		{
			printf("Can not multiply.To multiply the number of columns of 1st matrix and number of rows of 2nd matrix must be equal.\n");
		}
		else {
			int **arr3 = (int **)malloc(m1* sizeof(int *));
			for ( i = 0; i < m1; i++)
			{
				arr3[i]= (int *)malloc(n2 * sizeof(int));
			}
			
			for ( i = 0; i < m1; i++)
			{
				for (j = 0;j < n2; j++)
				{	
					arr3[i][j]=0;
					for (int k = 0; k < n1; k++)
					{
						arr3[i][j]=arr3[i][j] + arr[i][k] * arr2[k][j];
					}
					
				}
				
			}
			printf("The Answer is \n");
				for(i=0;i<m1;i++)
					for (j=0;j<n2;j++)
					{
						printf("%d\t",arr3[i][j]);
						if(j==n2-1){printf("\n");}
					}
			for (int i = 0; i < m1; i++) 
			{
       			free(arr3[i]);
   			}
    		free(arr3);
		}
	}

	for (int i = 0; i < m2; i++) 
	{
        free(arr2[i]);
    }
    free(arr2);

}

for (int i = 0; i < m1; i++) 
{
        free(arr[i]);
    }
    free(arr);
return 0;
}