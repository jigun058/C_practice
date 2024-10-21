void printList(List* L){
    SimpNode* p = L->head->next;

    while(p != NULL){
        printf("[%c] => ", p->data);
        p = p->next;
    }
    printf("\b\b\b     \n");
}