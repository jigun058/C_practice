#include <stdio.h>
#include <stdlib.h>

#define maxSize 100

typedef char operations;

typedef struct OpStack{
    operations op[maxSize];
    int top;
}OpStack;

void init(OpStack* S){
    S->top = -1;
}

int isEmpty(OpStack* S){
    return (S->top) == 0;
}

int isFull(OpStack* S){
    return (S->top) == (maxSize-1);
}

void push(OpStack* S, operations o){
    S->top += 1;
    S->op[S->top] = o;
}

operations pop(OpStack* S){
    operations temp = S->op[S->top];
    S->top -= 1;
    return temp;
}

operations peek(OpStack* S){
    return S->op[S->top];
}

int prio

int main() {
    OpStack stack;

    char* sick = (char*)malloc(sizeof(char)*200);
    scanf("%s", sick);

    char postfix[sizeof(sick)] = NULL;

    for(int i=0; sick[i]!='\0'; i++){
        if(sick[i] == '(' || sick[i] == ')' || sick[i] == '*' || sick[i] == '/' || sick[i] == '+' || sick[i] == '-')
        {
            checkPriority(&stack, sick[i]);
        }

    }

    return 0;
}