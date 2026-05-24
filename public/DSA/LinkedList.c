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
	newnode->next=NULL;
	return newnode;
}
void Display(struct Node* head)
{
	struct Node* ptr=head;
	printf("List is: ");
	while (ptr!=NULL)
	{
		printf("%d ",ptr->data);
		ptr=ptr->next;
	}
}
struct Node* InsertFront(struct Node* head,int ans)
{
	struct Node* new;
	//if (head==NULL)
	//	printf("List is empty\n");
	new=(struct Node*)malloc(sizeof(struct Node));
	new->data=ans;
	new->next=head;
	head=new;
	Display(head);
	return head;
}
struct Node* InsertEnd(struct Node* head,int ans)
{
	struct Node* new,*ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
		return 0;
	}
	new=(struct Node*)malloc(sizeof(struct Node));
	new->data=ans;
	new->next=NULL;
	ptr=head;
	while(ptr->next!=NULL)
		ptr=ptr->next;
	ptr->next=new;
	Display(head);
}
struct Node* InsertAfter(struct Node* head,int ans,int key)
{
	struct Node* new,*ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
		return 0;
	}
	new=(struct Node*)malloc(sizeof(struct Node));
	new->data=ans;
	ptr=head;
	while(ptr->data!=key && ptr!=NULL)
		ptr=ptr->next;
	if (ptr->data==key)
	{
		new->next=ptr->next;
		ptr->next=new;
		Display(head);
	}
	else printf("Data not fount");
}
struct Node* DeleteFront(struct Node* head)
{
	struct Node* ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
	}
	else
	{
		ptr=head;
		head=head->next;
		free(ptr);
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
		return 0;
	}
	else if(head->next==NULL)
	{
		free(head);
		head=NULL;
	}
	else
	{
		ptr=head;
		while(ptr->next!=NULL)
		{
			prev=ptr;
			ptr=ptr->next;
		}
		prev->next=NULL;
		free(ptr);
	}
	Display(head);
}
struct Node* DeleteAfter(struct Node* head,int key)
{
	struct Node* prev,*ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
		return 0;
	}
	ptr=head;
	while( ptr->next!=NULL)
	{
		if(ptr->data==key)
		{
			prev=ptr->next;
			ptr->next=prev->next;
			free(prev);
			break;
		}
		
		ptr=ptr->next;
	}
	Display(head);
}
int main()
{
	struct Node* head=NULL;
	struct Node* ptr=NULL;
	struct Node* newnode=NULL;
	int ans,inp,key;
	int choice;
	/*do
	{
		printf("Enter the data: ");
		scanf("%d",&ans);
		newnode=createNode(ans);
		if (head==NULL)
		{
			head=newnode;
		}
		else
		{
			ptr=head;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			ptr->next=newnode;
		}
		printf("Do you want to add another node? (Enter 1 for yes, 2 for no) ");
		scanf("%d",&choice);
	}while(choice);
	printf("\nLinked List is: ");
	Display(head);
	*/
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
				InsertEnd(head,inp);
				break;
			case 3:
				printf("\nEnter the data:");
				scanf("%d",&inp);
				printf("\nEnter the key:");
				scanf("%d",&key);
				InsertAfter(head,inp,key);
				break;
			case 4:
				head=DeleteFront(head);
				break;
			case 5:
				DeleteEnd(head);
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
