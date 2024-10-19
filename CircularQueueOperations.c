#include<stdio.h>
int Size(int rearPointer,int frontPointer)
{
	int count=0;
	for (int i=rearPointer; i>=frontPointer;i--)
	{
		count++;
	}	
	return count;
}

int IsFull(int rearPointer,int frontPointer,int s)
{	
	if ((rearPointer+1)%s==frontPointer)
	{
		return 1;
	}
	return 0;
}

int IsEmpty(int rearPointer,int frontPointer)
{	
	int size=Size(rearPointer,frontPointer);
	if (frontPointer==-1)
	{
		return 1;
	}
	return 0;
}

void Enqueue(int queue[],int *rearPointer,int *frontPointer,int s)
{
	if (IsFull(*rearPointer,*frontPointer,s))
	{
		printf("The Queue is full");
	}
	if (IsEmpty(*rearPointer,*frontPointer))
	{
		*rearPointer=0;
		*frontPointer=0;
	}
	else
		*rearPointer=(*rearPointer+1)%s;
	int item;
	printf("Enter the element to add\n");
	scanf("%d",&item);
	queue[*rearPointer]=item;
	
}

int dequeue(int queue[],int *rearPointer,int *frontPointer,int s)
{
	if (IsEmpty(*rearPointer,*frontPointer))
	{
		printf("The Queue is Empty");
	}
	if (*rearPointer==*frontPointer)
	{
		int temp=queue[*frontPointer];
		*rearPointer=*frontPointer=-1;
		return temp;
	}
	int size =Size(*rearPointer,*frontPointer);
	if (size>1)
	{
		int temp=queue[*frontPointer];
		*frontPointer=(*frontPointer+1)%s;
		return temp;
	}
}

void display(int queue[],int *rearPointer,int *frontPointer,int n)
{
	printf("ELements in the array are:\n");
	int size = Size(*rearPointer, *frontPointer);
	int i = *frontPointer;
	while (size--)
	{
		printf("%d ", queue[i]);
		i = (i + 1) % n;
	}
}

void main()
{
	int n,size,front=-1,rear=-1,result;
	printf("Enter the size of the queue\n");
	scanf("%d",&size);
	int queue[size];
	while(1)
	{
		printf("\nEnter 1 for Enqueue\n 2 for dequeue\n 3 for IsEmpty\n 4 for IsFull\n 5 for size\n 6 for exit\n");
		scanf("%d",&n);
		switch (n)
		{
			case 1: Enqueue(queue,&rear,&front,size);
				display(queue, &rear, &front, size);
				break;
			case 2: result=dequeue(queue,&rear,&front,size);
				printf("Removed element is %d\n",result);
				display(queue, &rear, &front, size);
				break;
			case 3:
				result = IsEmpty(rear, front, size);
				if (result==1)
					printf("Queue is Empty\n");
				else 
					printf("Queue is not empty\n");
				break;
			case 4: result=IsFull(rear,front,size);
				if (result==1)
					printf("Queue is Full\n");
				else 
					printf("Queue is not Full\n");
				break;
			case 5:	printf("size is %d\n",Size(rear,front));
				break;
			case 6:return;
			default:printf("Incorrect input\n");
		}
	}
}
