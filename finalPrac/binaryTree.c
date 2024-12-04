#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode {
    element key;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

TreeNode* makeNode(element key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

TreeNode* insertNode(TreeNode* root, element key) {
    TreeNode* x = root;
    TreeNode* y = NULL;
    TreeNode* z = makeNode(key);

    while(x != NULL) {
        y = x;
        if(key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if(y == NULL)
        root = z;
    else if(key < y->key)
        y->left = z;
    else
        y->right = z;

    return root;
}

TreeNode* searchNode(TreeNode* root, element key) {
    if(root == NULL || key == root->key)
        return root;

    while(root->key != key) {
        if(key < root->key)
            root = root->left;
        else
            root = root->right;
    }

    return root;
}

TreeNode* minNode(TreeNode* root) {
    while(root->left != NULL)
        root = root->left;
    
    return root;
}

TreeNode* maxNode(TreeNode* root) {
    while(root->right != NULL)
        root = root->right;
    
    return root;
}

//주의 : deleteNode에서 양쪽 자식 모두 있을 때에만 사용할 것.
TreeNode* successor(TreeNode* root) {
    return minNode(root->right);
}

void preOrder(TreeNode* root) {
    if(root == NULL)
        return;
    
    printf("[%d] ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

TreeNode* deleteNode(TreeNode* root, element key) {
    if(root == NULL)
        return NULL;

    if(key < root->key)
        root->left = deleteNode(root->left, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if(root->left == NULL) {
            TreeNode* tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL) {
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        else {
            TreeNode* tmp = successor(root);
            root->key = tmp->key;
            root->right = deleteNode(root->right, tmp->key);
        }
    }

    return root;
}

int main() {

    TreeNode* root = NULL;
    element keys[] = {35, 18, 7, 26, 12, 3, 68, 22, 30, 99};

    for(int i=0; i<10; i++){
        root = insertNode(root, keys[i]);
        preOrder(root);
        printf("\n");
    }
    printf("\n");

    //(searchNode(root, 22) != NULL) ? printf("Found\n") : printf("Not Found\n");
    printf("%d\n", successor(searchNode(root, 26))->key);

    root = deleteNode(root, 30); preOrder(root); printf("\n");
    root = deleteNode(root, 26); preOrder(root); printf("\n");

    return 0;


    return 0;
}


