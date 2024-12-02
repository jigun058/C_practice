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

int height(TreeNode* root)
{
    if(!root)
        return 0;
    else
        return 1 + MAX(height(root->left), height(root->right));    
}

int balance(TreeNode *root)
{
    if(root == NULL)
        return 0;
        
    return height(root->left) - height(root->right);    
}

TreeNode* insertNode(TreeNode* root, element key)
{
    if(root == NULL)
        return makeNode(key);
        
    if(key < root->key)
        root->left = insertNode(root->left, key);
    else if(key > root->key)
        root->right = insertNode(root->right, key);
    
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
    printf("Balance Factor : %d\n", balance(root));

    return 0;
}





