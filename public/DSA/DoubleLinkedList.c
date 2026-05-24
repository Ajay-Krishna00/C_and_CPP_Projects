#include<stdio.h>
#include<stdlib.h>
struct Node
{
	int data;
	struct Node* prev;
	struct Node* next;
};
struct Node* createNode(int val)
{
	struct Node* new=(struct Node*)malloc(sizeof(struct Node));
	new->data=val;
	new->prev = NULL;
    	new->next = NULL;
	return new;
}
void Display(struct Node* head)
{
	struct Node* ptr=head;
	printf("The List is: ");	
	while(ptr!=NULL)
	{
		printf("%d ",ptr->data);
		ptr=ptr->next;
	}
}
struct Node* InsertFront(struct Node* head,int val)
{
	struct Node* new=createNode(val);
	if(head==NULL)
	{
		head=new;
		Display(head);
		return head;
	}
	new->next=head;
	head=new;
	head->next->prev=new;
	new->prev=NULL;
	Display(head);
	return head;
}
struct Node* InsertEnd(struct Node* head,int val)
{
	struct Node* new=createNode(val);
	struct Node* ptr=head;
	if(head==NULL)
	{
		head=new;
		new->prev=head;
		Display(head);
		return head;
	}
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	new->next=NULL;
	new->prev=ptr;
	ptr->next=new;
	Display(head);
	return head;
}
struct Node* InsertAfterNode(struct Node* head,int val,int key)
{
	struct Node* new=createNode(val);
	struct Node* ptr=head;
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
	}
	while(ptr->data!=key && ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
	if(ptr->data==key)
	{
		
		new->prev=ptr;
		if(ptr->next!=NULL)
		{
			new->next=ptr->next;
			ptr->next->prev=new;
		}
		else
		{
			new->next=NULL;
		}
		ptr->next=new;
		Display(head);
		return head;
	}
	else{
		printf("The Key not found");
	}
	
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
		head->prev=NULL;
		free(ptr);
	}
	Display(head);
	return head;
}
struct Node* DeleteEnd(struct Node* head)
{
	struct Node* ptr;
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
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
			ptr=ptr->next;
		}
		ptr=ptr->prev;
		free(ptr->next);
		ptr->next=NULL;
	}
	Display(head);
}
struct Node* DeleteAfter(struct Node* head,int key)
{
	struct Node* ptr,*ptr2;
	if (head==NULL)
	{
		printf("List is empty\n");
		return head;
	}
	ptr=head;
	while(ptr->next!=NULL)
	{
		if(ptr->data==key)break;
		ptr=ptr->next;
	}
	if(ptr->data==key)
	{
		
		if(ptr->next==NULL)
		{
			printf("There are no node after %d to delete",key);
			return head;
		}
		ptr2=ptr->next;
		if(ptr->prev==NULL)
		{
			head=head->next;
			head->prev=NULL;
			free(ptr);
			return head;
		}
		if(ptr->next!=NULL && ptr2->next!=NULL)
		{
			ptr->next=ptr2->next;
			ptr2->next->prev=ptr;
			free(ptr2);
		}
		else if(ptr2->next==NULL)
		{
			ptr->next=NULL;
			free(ptr2);
		}
		
		Display(head);
		
	}
	else{
		printf("The Key not found");
	}
}
int main()
{
	struct Node* head=NULL;
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
				InsertEnd(head,inp);
				break;
			case 3:
				printf("\nEnter the data:");
				scanf("%d",&inp);
				printf("\nEnter the key:");
				scanf("%d",&key);
				InsertAfterNode(head,inp,key);
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
