#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef int element;

typedef struct TreeNode {
    element key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* makeNode(element key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

int getHeight(TreeNode* root) {
    if (!root) {
        return 0;
    }
    else {
        return (1 + MAX(getHeight(root->left), getHeight(root->right)));
    }
}

int getBalance(TreeNode* root) {
    if(root == NULL) {
        return 0;
    }
    
    return (getHeight(root->left) - getHeight(root->right));
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

TreeNode* insertNode(TreeNode* root, element key) {
    if (root == NULL) {
        return makeNode(key);
    }
    
    if (key < root->key) {
        root->left = insertNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }

    int balance = getBalance(root);

    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }

    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }

    if (balance <-1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    
    return root;
}