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
			if (arr[i][j]==0)
			{
				count++;
			}
		}
	}
	if (count> ((r*c)/2))
	{
		printf("Matrix is sparse\n");
		ans=((float)count/(r*c));
		printf("Sparcity is %.2f",ans);
	}
	else
	{
		printf("Matrix is not sparse ");
	}
}


