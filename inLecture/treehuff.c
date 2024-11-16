#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct {
    char alpha;
    char morseCode[N];
}Code;

Code table[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};

typedef struct TreeNode{
    char alpha;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* makeNode(char alpha, TreeNode* left, TreeNode* right){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->alpha = alpha;
    node->left = left;
    node->right = right;

    return node;
}

TreeNode* makeMorseTree(){
    TreeNode* root = makeNode(0, NULL, NULL);

    for(int i=0; i<26; i++){
        TreeNode* p = root;
        int n = strlen(table[i].morseCode);

        for(int j=0; j<n; j++){
            char c = table[i].morseCode[j];
            if(c == '.'){
                if(p->left == NULL)
                    p->left = makeNode(0, NULL, NULL);
                p = p->left;
            }
            else{
                if(p->right == NULL)
                    p->right = makeNode(0, NULL, NULL);
                p = p->right;
            }
        }
        p->alpha = table[i].alpha;
    }
    return root;
}

void preOrder(TreeNode* node){
    if(root->alpha == 0) {
        preOrder(root->left);
        preOrder(root->right);
    }
}

#define maxSize 100

typedef TreeNode* Element;

typedef struct QueueType{
    Element data[maxSize];
    int front;
    int rear;
}QueueType;

void init(QueueType *Q){
    Q->front = 0;
    Q->rear = 0;
}

int isEmpty(QueueType* Q){
    return (Q->front) == (Q->rear);
}

int isFull(QueueType* Q){
    return (Q->front) == (((Q->rear)+1)%maxSize);
}

void enqueue(QueueType* Q, Element e){
    if(isFull(Q)) printf("Overflow\n");
    Q->rear = ((Q->rear) + 1)%100;
    Q->data[Q->rear] = e;
}

void levelOrder(TreeNode* root){
    QueueType Q;
    init(&Q);

    enqueue(&Q, root);

    while(!isEmpty(&Q)){
        root = dequeue(&Q);
        printf("[%C] ", root->data);

        if(root->left != NULL)
            enqueue(&Q, root->left);
        if(root->right != NULL)
            enqueue(&Q, root->right);
    }
}

int main(){
    TreeNode* root = makeMorseTree();
    preOrder(root);

    return 0;
}