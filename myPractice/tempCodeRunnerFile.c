Stack S;

    initStack(&S);

    push(&S, 'A');
    push(&S, 'B');
    push(&S, 'C');
    push(&S, 'D');
    push(&S, 'E');
    push(&S, 'F');

    while(!isStackEmpty(&S)){
        printf("%c %c\n", peek(&S), pop(&S));
    }