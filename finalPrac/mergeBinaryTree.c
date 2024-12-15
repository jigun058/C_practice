#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
    element key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* makeNode(element key, TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    node->key = key;
    node->left = left;
    node->right = right;

    return node;
}

TreeNode* mergeTree(TreeNode* T1, TreeNode* T2) {
    if (T1 == NULL)
        return T2;

    if (T2 == NULL)
        return T1;

    TreeNode* root = makeNode(T1->key + T2->key, NULL, NULL);

    root->left = mergeTree(T1->left, T2->left);
    root->right = mergeTree(T1->right, T2->right);

    return root;
}

void preOrder(TreeNode* root) {
    if(root == NULL)
        return;
    
    printf("[%d] ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    TreeNode *N4 = makeNode(5, NULL, NULL);
    TreeNode *N3 = makeNode(2, NULL, NULL);
    TreeNode *N2 = makeNode(3, N4, NULL);
    TreeNode *T1 = makeNode(1, N2, N3);

    TreeNode *M6 = makeNode(7, NULL, NULL);
    TreeNode *M5 = makeNode(4, NULL, NULL);
    TreeNode *M3 = makeNode(3, NULL, M6);
    TreeNode *M2 = makeNode(1, NULL, M5);
    TreeNode *T2 = makeNode(2, M2, M3);

    TreeNode *root = mergeTree(T1, T2);
    preOrder(root);

    return 0;
}