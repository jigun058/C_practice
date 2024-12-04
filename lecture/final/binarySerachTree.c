#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct TreeNode{
    element key;
    struct TreeNode *left, *right, *parent;
}TreeNode;

TreeNode* makeNode(element key){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

TreeNode* insertNode(TreeNode* root, element key){
    // parent 있는 버전
    TreeNode* y = NULL;
    TreeNode* x = root;
    TreeNode* z = makeNode(key);

    while(x != NULL){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if(y == NULL)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;

    // parent 없는 버전
    // if(root == NULL)
    //     return makeNode(key);

    // if(key < root->key)
    //     root->left = insertNode(root->left, key);
    // else if(key > root->key)
    //     root->right = insertNode(root->right, key);

    return root;
}

TreeNode* searchNode(TreeNode* root, element key){
    if(root == NULL || key == root->key)
        return root;
    
    if(key < root->key)
        return searchNode(root->left, key);
    else
        return searchNode(root->right, key);
}

TreeNode* minNode(TreeNode* root){
    TreeNode* p = root;
    while(p->left != NULL)
        p = p->left;

    return p;
}

TreeNode* maxNode(TreeNode* root){
    TreeNode* p = root;
    while(p->right != NULL)
        p = p->right;

    return p;
}

TreeNode* successor(TreeNode* root){
    TreeNode* x = root;
    if(x->right != NULL)
        return minNode(x->right);
    
    //중요하게 생각하신대!!!!!!!!!
    TreeNode* y = x->parent;
    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;

    // TreeNode* p = root;
    // while(p->left != NULL)
    //     p = p->left;
    // return p;
}

void preOrder(TreeNode* root){
    if(root != NULL){
        printf("[%d] ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(TreeNode* root){
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

TreeNode* deleteNode(TreeNode* root, element key){
    if(root == NULL)
        return NULL;
    
    if(key < root->key)
        root->left = deleteNode(root->left, key);
    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else{
        if(root->left == NULL){
            TreeNode* tmp = root->right;
            free(root);
            return tmp;
        }
        else if(root->right == NULL){
            TreeNode* tmp = root->left;
            free(root);
            return tmp;
        }
        else{
            TreeNode* tmp = successor(root);
            root->key = tmp->key;
            root->right = deleteNode(root);
        }
    }
    return root;
}

TreeNode* deleteNodeIter(TreeNode* root, element key)    //삭제 연산   11.7 작 성 
{
   TreeNode *x, *y;
   TreeNode *z = searchNode(root, key);
   
   // z를 이용해 y찾기  
   if(z->left == NULL || z->right == NULL)
      y = z;
   else
      y = successor(z);
   
   // 2. x 찾기  
   if(y->left != NULL)  //y의 왼쪽 자식이 없다면... 
      x = y->left; // y를 살려야하니까 x는 y의 왼쪽 자식이 됨.
   else
      x = y->right; 
   
   //3. x 기준 자신의 할부지의 위치에 따라 케이스를 나눠서 삭제함. 
   if(x != NULL)
      x->parent = y->parent;    // (x기준) 내 부모가 없어지니까 내 부모의 부모(할부지)랑 연결되는거임. 
   
   if(y->parent == NULL)  // (x기준) 내 부모가 루트노드라면.. 
      root = x;
   else if(y == y->parent->left) // (x기준) 내부모가 할부지의 왼쪽 자식이라면.. 
      y->parent->left = x;
   else                    // (x기준) 내부모가 할부지의 오른쪽  자식이라면.. 
      y->parent->right = x; 
   
   //4. 왼쪽, 오른쪽 자식을 모두 갖는 노드의 삭제 => 해당 노드를 후계자 노드의 키값으로 바꾼다. 
   if(y != z)       //case 3임.
      z->key = y->key; 
   return root;
}

int main(){
    TreeNode* root = NULL;
    element keys[] = {35, 18, 7, 26, 12, 3, 68, 22, 30, 99};

    for(int i=0; i<10; i++){
        root = insertNode(root, keys[i]);
        preOrder(root);
        printf("\n");
    }
    printf("\n");

    //(searchNode(root, 22) != NULL) ? printf("Found\n") : printf("Not Found\n");
    printf("%d\n", successor(searchNode(root, 18))->key);

    root = deleteNode(root, 30); preOrder(root); printf("\n");
    root = deleteNode(root, 26); preOrder(root); printf("\n");

    return 0;
}