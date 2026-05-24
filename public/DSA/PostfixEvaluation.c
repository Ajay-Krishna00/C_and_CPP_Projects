#include<stdio.h>
#include<stdbool.h>
#include<math.h>
int stack[20];
int top=-1;

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
			break;
		case '-':return true;
			break;
		case '*':return true;
			break;
		case '/':return true;
			break;
		case '^':return true;
			break;
		case ')':return true;
			break;
		case '(':return true;
			break;
		default:return false;
	}
}
int main()
{
	int n;
	char inp[20];
	printf("Enter the length of the Postfix expression ");
	scanf("%d",&n);
	if (n > 20) 
	{
		printf("Length exceeds maximum allowed size of 20\n");
		return 1;
  }
	printf("Enter the elements of the Postfix expression ");
	for (int i=0;i<n;i++)
	{
		scanf(" %c",&inp[i]);
	}
	int i=0;
	while(i!=n)
	{
		if(!IsOperator(inp[i]))
		{
			int l=inp[i]-'0';
			Push(l);
		}
		else
		{
			int O2=Pop();
			int O1=Pop();
			int r;
			switch (inp[i])
			{
				case '+': r=O1+O2;
					break;
				case '-': r=O1-O2;
					break;
				case '*': r=O1*O2;
					break;
				case '/': r=O1/O2;
					break;
				case '^': r=pow(O1,O2);
					break;
			}
			Push(r);
		}
		i+=1;
	}
	int result=Pop();
	printf("The Result is: %d",result);
	return 0;
}


