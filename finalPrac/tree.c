#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a >= b) ? a : b)

typedef char Telement;

typedef struct TreeNode {
    Telement e;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* makeNode(Telement e, TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->e = e;
    node->left = left;
    node->right = right;

    return node;
}

void preOrder(TreeNode* root) {
    if(!root)
        return;
    printf("%c", root->e);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode* root) {
    if(!root)
        return;
    inOrder(root->left);
    printf("%c", root->e);
    inOrder(root->right);
}

void postOrder(TreeNode* root) {
    if(!root)
        return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c", root->e);
}

int nodeCount(TreeNode* root) {
    if(!root)
        return 0; 
    return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int isExternal(TreeNode* node) {
    return node->left == NULL && node->right == NULL;
}

int leafNodeCount(TreeNode* root) {
    if(!root)
        return 0;
    else {
        if(isExternal(root))
            return 1;
        else
            return leafNodeCount(root->left) + leafNodeCount(root->right);
    }
}

int height(TreeNode* root) {
    if(!root)
        return 0;
    else {
        return 1 + MAX(height(root->left), height(root->right));
    }
}

void treeReverse(TreeNode* root) {
    if(!root)
        return;

    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    treeReverse(root->left);
    treeReverse(root->right);
}

int main() {

    TreeNode* N4 = makeNode('D', NULL, NULL);
    TreeNode* N5 = makeNode('E', NULL, NULL);
    TreeNode* N6 = makeNode('F', NULL, NULL);
    TreeNode* N2 = makeNode('B', N4, N5);
    TreeNode* N3 = makeNode('C', N6, NULL);
    TreeNode* N1 = makeNode('A', N2, N3);
    
    preOrder(N1); printf("\n");
    inOrder(N1); printf("\n");
    postOrder(N1); printf("\n"); printf("\n");

    printf("Node Count : %d\n", nodeCount(N1));
    printf("Leaf Node Count : %d\n", leafNodeCount(N1));
    printf("Tree height : %d\n", height(N1));

    treeReverse(N1); printf("\n");
    intOrder(N1); printf("\n");

    return 0;
}