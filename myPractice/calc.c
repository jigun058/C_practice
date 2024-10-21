#include <stdio.h>
#include <stdlib.h>

typedef char Element;

typedef struct SimpNode{
    struct SimpNode* next;
    Element data;
}SimpNode;

typedef struct Stack{
    SimpNode* top;
}Stack;

void init(Stack* S){
    S->top = NULL;
}

int isEmpty(Stack* S){
    return S->top ==NULL;
}

int push(Stack* S, Element e){
    SimpNode* node = (SimpNode*)malloc(sizeof(SimpNode));
    node->data = e;
    
    node->next = S->top;
    S->top = node;

    return 0;
}

Element pop(Stack* S){
    if(isEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    SimpNode* node = S->top;
    Element temp = node->data;
    S->top = node->next;

    return temp;
}

Element peek(Stack* S){
    if(isEmpty(S)){
        printf("Underflow\n");
        return -1;
    }

    return S->top->data;
}

int checkOperator(char ch){
    if(ch == '+' || ch == '-'){
        return 1;
    }
    else if(ch == '*' || ch == '/'){
        return 2;
    }
    else{
        return 0;
    }
}

int calc(char op1, char op2, char oper){
    int num1 = op1 - '0';
    int num2 = op2 - '0';

    switch (oper){
    case '+':
        return num1+num2;
    
    case '-':
        return num1-num2;

    case '*':
        return num1*num2;

    case '/':
        return num1/num2;
    }
    return -1;
}

int main() {
    Stack S;
    init(&S);

    char* str = (char*)malloc(sizeof(char)*100);

    scanf("%s", str);

    for(int i=0; str[i]!='\0'; i++){
        char temp = str[i];
        if (checkOperator(temp) == 0){
            push(&S, temp);
            continue; 
        }
        else if(checkOperator(temp) != 0){
            char op2 = pop(&S);
            char op1 = pop(&S);
            int result = calc(op1, op2, temp);
            char op = result + '0';
            
            push(&S, op);
        }
    }

    printf("%c\n", pop(&S));

    return 0;
}