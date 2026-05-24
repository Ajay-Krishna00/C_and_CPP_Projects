#include<stdio.h>
int BinarySearch(int target,int arr[],int n)
{
	int lft_pointer=0;
	int right_pointer=n-1;
	int mid;
	while (lft_pointer<right_pointer)
	{
		mid=(lft_pointer + right_pointer)/2;
		if (target==arr[mid]) return mid;
		else if (target>arr[mid]) 
		{
			lft_pointer=mid+1;
		}
		else if (target<arr[mid]) 
		{
			right_pointer=mid-1;
		}
		else return -1;
	}
}
void main()
{
	int n,arr[50],target,result;
	printf("Enter the size of the array ");
	scanf("%d",&n);
	printf("Enter the elements of the array\n");
	for (int i=0; i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	printf("Enter the element you want to search ");
	scanf("%d",&target);
	result=BinarySearch(target,arr,n);
	if (result!=-1)
	{
		printf("Element is at index %d\n",result);
	}
	else printf("Element not found\n");
}



