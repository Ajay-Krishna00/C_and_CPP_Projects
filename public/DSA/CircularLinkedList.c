#include<stdio.h>
#include<stdlib.h>
 struct Node
{
	int data;
	struct Node* next;
};
struct Node* createNode(int val)
{
	struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
	newnode->data=val;
	newnode->next=newnode;
	return newnode;
}
void Display(struct Node* head)
{
	struct Node* ptr=head;
	printf("List is: ");
	do {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    	} while (ptr != head);
}
struct Node* InsertFront(struct Node* head,int ans)
{
	struct Node* new=createNode(ans);
	struct Node* ptr=head;
	if (head==NULL)
	{
		head=new;
		new->next=head;
	}
	else
	{
		while(ptr->next!=head)
		{
			ptr=ptr->next;
		}
		new->next=head;
		head=new;
		ptr->next=head;
	}
	Display(head);
	return head;
}
struct Node* InsertEnd(struct Node* head,int ans)
{
	struct Node* new,*ptr;
	new=createNode(ans);
	ptr=head;
	if (head==NULL)
	{
		head=new;
		new->next=head;
	}
	else
	{
		while(ptr->next!=head)
			ptr=ptr->next;
		ptr->next=new;
		new->next=head;
	}
	Display(head);
	return head;
}
struct Node* InsertAfter(struct Node* head,int ans,int key)
{
	struct Node* new,*ptr;
	new=createNode(ans);
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
	}
	ptr=head;
	while(ptr->data!=key)
		ptr=ptr->next;
	if (ptr->data==key)
	{
		if(ptr==head)
		{
			return InsertFront(head,ans);
		}
		else if(ptr->next==head)
		{
			return InsertEnd(head,ans);
		}
		else
		{
			new->next=ptr->next;
			ptr->next=new;
			Display(head);
		}
	}
	else printf("Data not fount");
}
struct Node* DeleteFront(struct Node* head)
{
	struct Node* ptr,*temp;
	ptr=head;
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
	}
	else if (head->next==head)
	{
		head=NULL;
		free(ptr);
	}
	else
	{
		temp=head;
		while(ptr->next!=head)
		{
			ptr=ptr->next;
		}
		head=head->next;
		ptr->next=head;
		free(temp);
	}
	Display(head);
	return head;
}
struct Node* DeleteEnd(struct Node* head)
{
	struct Node* ptr,*prev;
	if (head==NULL)
	{
		printf("List is empty\n");
		
	}
	else if(head->next==head)
	{
		free(head);
		head=NULL;
	}
	else
	{
		ptr=head;
		while(ptr->next!=head)
		{
			prev=ptr;
			ptr=ptr->next;
		}
		prev->next=head;
		free(ptr);
	}
	Display(head);
	return head;
}
struct Node* DeleteAfter(struct Node* head,int key)
{
	struct Node* prev,*ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
	}
	ptr=head;
	while( ptr->next!=head)
	{
		if(ptr->data==key)
		{
			if(ptr==head)
			{
				return DeleteFront(head);
			}
			else if(ptr->next==head)
			{
				return DeleteEnd(head);
			}
			else
			{
				prev=ptr->next;
				ptr->next=prev->next;
				free(prev);
				break;
			}
		}
		
		ptr=ptr->next;
	}
	if(ptr->data!=key)
	{
		printf("THe key was not found");
	}
	Display(head);
	return head;
}
int main()
{
	struct Node* head=NULL;
	struct Node* ptr=NULL;
	struct Node* newnode=NULL;
	int ans,inp,key;
	int choice;
	printf("What Operation Do you want to perform?");
	while(1)
	{
		printf("\nEnter 1 for Intertion at Front\n\t2 for Intertion at end\n\t3 for Intertion after a node\n\t4 for Deletion at Front\n\t5 for Deletion at end\n\t6 for Deletion after a node\n\t7 to exit\n");
		scanf("%d",&ans);
		switch (ans)
		{
			case 1:
				printf("\nEnter the data:");
				scanf("%d",&inp);
				head=InsertFront(head,inp);
				break;
			case 2:
				printf("\nEnter the data:");
				scanf("%d",&inp);
				head=InsertEnd(head,inp);
				break;
			case 3:
				printf("\nEnter the data:");
				scanf("%d",&inp);
				printf("\nEnter the key:");
				scanf("%d",&key);
				head=InsertAfter(head,inp,key);
				break;
			case 4:
				head=DeleteFront(head);
				break;
			case 5:
				head=DeleteEnd(head);
				break;
			case 6:
				printf("\nEnter the key:");
				scanf("%d",&key);
				DeleteAfter(head,key);
				break;
			case 7:
				return 0;
			default:printf("Invalid input");
		}
	}
	
}
