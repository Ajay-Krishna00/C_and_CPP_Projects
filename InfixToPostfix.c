#include<stdio.h>
#include<stdbool.h>
char stack[20];
char arr[20];
int top=-1;
int indexs=-1;

void AddArray(char element)
{
	indexs+=1;
	arr[indexs]=element;
}
void Push(char element)
{
	top+=1;
	stack[top]=element;
}
int Pop()
{
	char temp=stack[top];
	top-=1;
	return temp;
}
bool IsOperator(char element)
{
	switch(element)
	{
		case '+':return true;
		case '-':return true;
		case '*':return true;
		case '/':return true;
		case '^':return true;
		case ')':return true;
		case '(':return true;
		default:return false;
	}
}
int priority(char element)
{
	switch(element)
	{
		case '+':return 1;
		case '-':return 1;
		case '*':return 2;
		case '/':return 2;
		case '^':return 3;
		case '(':return 0;
	}
}
int Assign(char element)
{
	if (!IsOperator(element))
	{
		AddArray(element);
	}
	else
	{
		if (top==-1)
			Push(element);
		else if (element == '(' || element == '^')
			Push(element);
		else if (element==')')
		{
			while (stack[top]!='(')
			{
				AddArray(Pop());
			}
			if (stack[top]=='(') Pop();
		}
		else 
		{
			while (priority(stack[top])>=priority(element))
			{
				AddArray(Pop());
			}
			Push(element);
		}
	}
}

int main()
{
	int n;
	char inp[20];
	printf("Enter the length of the expression ");
	scanf("%d",&n);
	if (n > 20) 
	{
		printf("Length exceeds maximum allowed size of 20\n");
		return 1;
  }
	printf("Enter the elements of the expression ");
	for (int i=0;i<n;i++)
	{
		scanf(" %c",&inp[i]);
		Assign(inp[i]);
	}
	while (top!=-1)
	{
		AddArray(Pop());
	}
	printf("The postfix expression is\n");
	for (int i=0;i<=indexs;i++)
	{
		printf("%c ",arr[i]);
	}
	return 0;
}



