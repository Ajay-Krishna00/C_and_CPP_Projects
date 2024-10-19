#include <stdio.h>
#include<string.h>

int top = -1;
#define MAXLEN 50

void push(char c, char stack[])
{
  top++;
  stack[top] = c;
}

char pop(char stack[])
{
  if (top==-1)
  {
    printf("Stack is empty");
    return 0;
  }
  char temp = stack[top];
  top--;
  return temp;
}

void main()
{
  int n, count = 0;
  char inp[MAXLEN], stack[MAXLEN];
  printf("Enter the string\n");
  fgets(inp, MAXLEN, stdin);
  inp[strcspn(inp, "\n")] = '\0';
  n=strlen(inp);
  for (int i = 0; i < n; i++)
  {
    push(inp[i], stack);
  }
  for (int i = 0; i < n; i++)
  {
    if (pop(stack) != inp[i])
    {
      count++;
    }
  }
  if (count == 0)
  {
    printf("The string is palindrome!\n");
  }
  else
  {
    printf("The string is NOT palindrome!\n");
  }
}