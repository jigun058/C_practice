#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef int element;

typedef struct TreeNode
{
    element key;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

TreeNode* makeNode(element key)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int getHeight(TreeNode* root)
{
    if(!root)
        return 0;
    else
        return 1 + MAX(getHeight(root->left), getHeight(root->right));    
}

int getBalance(TreeNode *root)
{
    if(root == NULL)
        return 0;
        
    return getHeight(root->left) - getHeight(root->right);    
}

TreeNode* rotateLeft(TreeNode* p) {
    TreeNode* c = p->right;
    p->right = c->left;
    c->left = p;

    return c;
}

TreeNode* rotateRight(TreeNode* p) {
    TreeNode* c = p->left;
    p->left = c->right;
    c->right = p;

    return c;
}

TreeNode* insertNode(TreeNode* root, element key)
{
    if(root == NULL)
        return makeNode(key);
        
    if(key < root->key)
        root->left = insertNode(root->left, key);
    else if(key > root->key)
        root->right = insertNode(root->right, key);

    int balance = getBalance(root);

    if(balance < -1 && key > root->right->key) { //rr type -> RotateLeft (책에서는 rr회전)
        return rotateLeft(root);
    }

    if(balance > 1 && key < root->left->key) { //ll type
        return rotateRight(root);
    }

    if(balance <-1 && key < root->right->key) { // rl type
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if(balance > 1 && key > root->left->key) { //lr type
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    
    return root;    
}

void preOrder(TreeNode *root)
{
    if(root)
    {
        printf("[");
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
        printf("]");
    }
}

void display(TreeNode *root, int key)
{
    printf("[Insert %d] : ", key);
    preOrder(root);
    printf("\n");
}

int main()
{
    TreeNode *root = NULL;
    int data[] = {7, 8, 9, 2, 1, 5, 3, 6, 4};
    
    for(int i = 0; i < 9; i++)
    {
        root = insertNode(root, data[i]);
        display(root, data[i]);
    }

    printf("\n");
    printf("Balance Factor : %d\n", getBalance(root));

    return 0;
}





