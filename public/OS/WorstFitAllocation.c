
// worst fit

#include <stdio.h>
#include <stdlib.h>

struct memory
{
  int blockSize;
  int procSize;
  int freeSize;
  struct memory *next;
};

struct memory *head = NULL;
struct memory *temp = NULL;

struct memory *createMem(int size)
{
  struct memory *newMem = (struct memory *)malloc(sizeof(struct memory));
  newMem->blockSize = size;
  newMem->freeSize = size;
  newMem->procSize = 0;
  if (head == NULL)
  {
    newMem->next = NULL;
    head = newMem;
  }
  else
  {
    newMem->next = head;
    head = newMem;
  }
}
int allocMem(int size)
{
  struct memory *ptr = head;
  temp = ptr;
  while (ptr)
  {
    if (size <= (ptr->freeSize) && temp->freeSize < ptr->freeSize)
    {
      temp = ptr;
    }
    ptr = ptr->next;
  }

  if (size <= (temp->freeSize))
  {
    temp->procSize = temp->procSize + size;
    temp->freeSize = temp->freeSize - size;
    return 1;
  }
  return 0;
}

void printMemoryStatus()
{
  struct memory *current_block = head;

  while (current_block)
  {
    printf("Block Size: %d Process Size:%d, Free Space: %d\n", current_block->blockSize, current_block->procSize, current_block->freeSize);
    current_block = current_block->next;
  }
}

int main()
{
  createMem(200);
  createMem(100);
  createMem(300);
  createMem(500);
  printMemoryStatus();
  int ch, size;
  do
  {
    printf("\nMenu\n----\n1.Alllocate\n2.Display\n3.Exit\n");
    printf("\nEnter the choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      printf("Enter the size of the process..:");
      scanf("%d", &size);
      if (allocMem(size))
        printf("Memory allocated successfully.\n");
      else
        printf("Insufficient memory.\n");

      printf("Memory Status After Allocation:\n");
      printMemoryStatus();
      break;
    case 2:
      printf("Memory Status ........:\n");
      printMemoryStatus();
      break;

    case 3:
      exit(0);
    default:
      printf("Invalid Choice....");
    }
  } while (1);

  return 0;
}
