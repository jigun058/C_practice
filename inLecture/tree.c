#include <stdio.h>
#include <stdlib.h>

Code table[] = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};

typedef char Telement;

typedef struct{
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* makeNode(Telement e, TreeNode* left, TreeNode* right){

}





int nodeCount(TreeNode* root){
    if(!root)
        return 0;
    else
        return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int isExternal(TreeNode* root){
    return (root->left == NULL && root->right == NULL);
}

int leafNodeCount(TreeNode* root){
    if(!root)
        return 0;
    else{
        if(isExternal(root))
            return 1;
        else
            return leafNodeCount(root->left) + leafNodeCount();
    }
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int height(TreeNode* root){
    if(!root)
        return 0;
    else
        return 1 + MAX(height(root->left), height(root->right));
}

void treeReverse(TreeNode* root){
    if(root){
        
    }
    
}

int main(){
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
    inOrder(N1); printf("\n");

    return 0;
}