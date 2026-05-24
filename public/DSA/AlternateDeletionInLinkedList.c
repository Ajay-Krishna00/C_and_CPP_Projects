#include <stdio.h>
#include <stdlib.h>
struct node
{
  int data;
  struct node *next;
};
void Display(struct node *head)
{
  struct node *ptr = head;
  printf("List is: ");
  while (ptr != NULL)
  {
    printf("%d ", ptr->data);
    ptr = ptr->next;
  }
}
struct node *CreateNode(struct node * head,int d)
{
  struct node *new = (struct node*)malloc(sizeof(struct node));
  new->data = d;
  new->next = NULL;
  return new;
}
struct node *InsertionFront(struct node *head,int d)
{
  struct node *new = CreateNode(head,d);
  if (head==NULL)
  {
    head = new;
    return head;
  }
  new->next = head;
  head = new;
  Display(head);
  return head;
}
struct node *InsertionEnd(struct node *head,int d)
{
  struct node *ptr=head;
  struct node *new = CreateNode(head, d);
  if (head==NULL)
  {
    head = new;
    return head;
  }
  while(ptr->next!=NULL)
    ptr = ptr->next;
  ptr->next = new;
  Display(head);
  return head;
}
struct node *InsertionAfter(struct node *head,int d,int k)
{
  struct node *ptr=head;
  struct node *new = CreateNode(head, d);
  if (head==NULL)
  {
    printf("List is empty");
    return head;
  }
  while(ptr!=NULL && ptr->data!=k)
    ptr = ptr->next;
  if(ptr->data==k)
    {
    new->next = ptr->next;
    ptr->next = new;
    Display(head);
    }
    else{
    printf("Key not found!");
    return head;
    }
  return head;
}
struct node *DelEven(struct node *head)
{
  struct node *ptr, *prev;
  ptr = head;
  prev = NULL;
  int index=1;

  while (ptr != NULL)
  {
    if (index % 2 == 0)
    { 
      struct node *temp = ptr;
      if (prev != NULL)
      {
        prev->next = ptr->next;
      }
      else
      {
        head = ptr->next; // Update head if the first node is even
      }
      ptr = ptr->next;
      free(temp);
    }
    else
    {
      prev = ptr;
      ptr = ptr->next;
    }
    index++;
  }
  Display(head);
  return head;
}
struct node *DelOdd(struct node *head)
{
  struct node *ptr, *prev;
  ptr = head;
  prev = NULL;
  int index=1;
  while(ptr!=NULL)
  {
    if (index % 2 != 0)
    {
      struct node *temp = ptr;
      if (prev!=NULL)
      {
        prev->next = ptr->next;
      }
      else{
        head = ptr->next;
      }
      ptr = ptr->next;
      free(temp);
    }
    else{
      prev = ptr;
      ptr = ptr->next;
    }
    index++;
  }
  Display(head);
  return head;
}

int main()
{
  struct node *head = NULL;
  int inp,d,k;
  while(1)
  {
    printf("\nEnter 1 for Insertion at Front\n 2 for Insertion at END\n 3 for Insertion after a node\n 4 for Deletion in even places\n 5 for deletion in odd places \n 6 to exit\n");
    scanf("%d", &inp);
    if (inp==1 ||inp==2 ||inp==3)
    {
      printf("Enter the Data: ");
      scanf("%d", &d);
      if(inp==3)
      {
        printf("Enter the key: ");
        scanf("%d", &k);
      }
    }
    switch(inp)
    {
      case 1:
        head = InsertionFront(head,d);
        break;
      case 2:
        head = InsertionEnd(head,d);
        break;
      case 3:
        head = InsertionAfter(head,d,k);
        break;
      case 4:
        head=DelEven(head);
        break;
      case 5:
        head=DelOdd(head);
        break;
      case 6:
        return 0;
        break;
      default:
        printf("Invalid input");
        return 0;
    }
  }
  return 0;
}