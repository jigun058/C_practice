#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

typedef char element;

typedef struct
{
	element data[N];
	int top;
}StackType;


void init(StackType *S)
{
	S->top = -1;
}	

int isEmpty(StackType *S)
{
	return S->top == -1;
}

int isFull(StackType *S)
{
	return S->top == N-1;
}

void push(StackType *S, element e)
{
	if(isFull(S))	//&S는 아니다!
		printf("Overflow");
	else
	{
		S->top++;
		S->data[S->top] = e;
	}
}

int main()
{
	StackType S;
	init(&S);

	push(&S, 'C');
	push(&S, 'a');
	push(&S, 't');
	push(&S, 's');

	return 0;
}

/*
int ()
{
    StackType S;
    init(&S);
    
    char str[100];
    
    fgets(str, N, stdin);
    
    int n = strlen(str);
    
    for(int i = 0; i<n ; i++)
        push(&S, str[i]);
    
    while(!isEmpty(&S))
        printf("%c", pop(&S));
    
    print("\n");
    
}
*/


	for(int i = S->top; i>=0; i--)
		printf("%c ", S->data[i]);
	printf("\n");

int eval(char expr[])
{
	StackType S;
	init(&S);

	int op1, op2, num;
	char c;

	int n = strlen(expr);
	for(int i=0; i<n; i++)
	{
		c = expr[i];
		if(c >= '0' && c <= '9')
		{
			num = c - '0';
			push(&S, num);
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/')
		{
			op2 = pop(&S);
			op1 = pop(&S);

			switch (c)
			{
			case '+': push(&S, op1 + op2); break;
			case '-': push(&S, op1 - op2); break;
			case '*': push(&S, op1 * op2); break;
			case '/': push(&S, op1 / op2); break;
			}
		}
	}
	return pop(&S);
}

int 연산자 우선순위(char op)
{
	case 괄호
		1
	case + | -
		2
	case * | /
		3
}

void infixToPostfix(char expr[])
{
	StackType S;
	init(&S);

	char c, op;
	int n = strlen(expr);

	for(int i = 0; i<n; i++)
	{
		c = expr[i];
		if(C >= '0' && C <= '9')
			printf("%c ", c);
		else if(c == '(')
			push(&S, c);
		else if(c == ')')
		{
			op = pop(&S);
			while(op != '(')
			{
				printf("%c ", op);
				op = pop(&S);
			}
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/')
		{
			while(!isEmpty(&S))
			{
				op = peek(&S);
				if( /*연산자 우선순위(c) <= 연산자 우선순위(op)*/ )
					//pop & print
				else
					break;
			}
			push(c);
		}
	}

	//while(!isEmpty(&S))
		//pop & print
}

int main()
{
	char str[N];
	fgets(str, N, stdin);

	infixToPostfix(str);

	return 0;
}