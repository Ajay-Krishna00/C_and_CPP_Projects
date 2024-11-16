#include<stdio.h>
int top=-1;

void display(int arr[],int size)
{
	printf("ELements in the array are:\n");
	for (int i=top;i>=0;i--)
	{
		printf("| %d |\n",arr[i]);
	}
}
int push(int arr[],int size)
{
	printf("Enter the element to push\n");
	int n;
	scanf("%d",&n);
	
	if (top == size) return -1;
	else 
	{
		top+=1;
		arr[top]=n;
	}
}
int pop(int arr[])
{
	if (top ==-1) return -1;
	else 
	{
		int n=arr[top];
		top-=1;
		return n;
	}
}
int peek(int arr[])
{
	if (top ==-1) return -1;
	return arr[top];
}
int IsEmpty()
{
	if (top ==-1) return -1;
}
void main()
{
	int arr[50],n,result,size;
	char ans;
	printf("Enter size of the array\n");
	scanf("%d",&size);
	while(1)
	{
		printf("Enter 1 for push\n 2 for pop\n 3 for peek\n 4 for IsEmpty\n 5 for size\n 6 for exit\n");
		scanf("%d",&n);
		switch (n)
		{
			case 1: result=push(arr,size);
				if (result==-1)
					printf("Stack is Full\n");
				else display(arr,size);
				break;
			case 2: result=pop(arr);
				if (result==-1)
					printf("Stack is Empty\n");
				else 
				{
					printf("removed element is %d\n",result);
					display(arr,size);
				}
				break;
			case 3: result=peek(arr);
				if (result==-1)
					printf("Stack is Empty\n");
				else 
				{
					printf("Element is %d\n",result);
					display(arr,size);
				}
				break;
			case 4: result=IsEmpty();
				if (result==-1)
					printf("Stack is Empty\n");
				else 
					printf("Stack is not empty\n");
				break;
			case 5: int count=0;
				for (int i=top; i>=0;i--)
			{
				count++;
			}
				printf("size is %d\n",count);
				break;
			case 6:return;
			default:printf("Incorrect input\n");
		}
		
	}
}

