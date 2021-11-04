#include<iostream>
#define SIZE 100

typedef char element;
typedef struct stackType
{
	element data[SIZE];
	int top;
}StackType;

void initializeStack(StackType* s)
{
	s->top = -1;
}

bool isFull(StackType* s)
{
	if (s->top == SIZE - 1) return true;

	else return false;
}

bool isEmpty(StackType* s)
{
	if (s->top == -1) return true;

	else return false;
}

void push(StackType* s, element item)
{
	if (isFull(s)) return;

	s->top++;
	s->data[s->top] = item;
}

element pop(StackType* s)
{
	if (isEmpty(s)) exit(0);

	element temp;
	temp = s->data[s->top];
	s->top--;

	return temp;
}

element peek(StackType* s)
{
	if (isEmpty(s)) exit(0);

	return s->data[s->top];
}

bool checkParenthesis(const char* str)
{
	StackType s;
	char ch1;
	char ch2;

	initializeStack(&s);

	for (int i = 0; i < strlen(str); i++)
	{
		ch1 = str[i];

		switch (ch1)
		{
		case'(':
		case'{':
		case'[':
			push(&s, ch1);
			break;
			
		case')':
		case'}':
		case']':
			// 스택이 비어있을 시 -> 열리는 괄호가 없을 시
			if (isEmpty(&s)) 
				return false;
			
			ch2 = pop(&s);

			// 닫히는 괄호와 스택에서 pop한 열리는 괄호의 짝이 맞지 않을 시
			if ((ch1 == ')' && ch2 != '(') || (ch1 == '}' && ch2 != '{') || (ch1 == ']' && ch2 != '['))
			{
				return false;
				break;
			}
		}
	}
	// 스택에 아직 남아있는 열리는 괄호가 있을 시
	if (!isEmpty(&s)) 
		return false;

	return true;
}

int main()
{
	if (checkParenthesis("{(asfa)}"))
	{
		printf("True\n");
	}
	else printf("False\n");

	if (checkParenthesis("{)}"))
	{
		printf("True\n");
	}
	else printf("False\n");

	return 0;
}