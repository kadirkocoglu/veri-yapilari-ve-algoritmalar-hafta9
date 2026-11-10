#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

static int height(Node *n) { return n ? n->height : 0; }

static int max(int a, int b) { return a > b ? a : b; }

static void updateHeight(Node *n) {
    n->height = 1 + max(height(n->left), height(n->right));
}


static int balanceFactor(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

static Node *newNode(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}


static Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x; 
}


static Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y; 
}


Node *insertAVL(Node *root, int key) {
    
    if (root == NULL) return newNode(key);

    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    else
        return root; 

    
    updateHeight(root);

    
    int bf = balanceFactor(root);

    

    
    if (bf > 1 && key < root->left->key) {
        printf("  [%d dugumunde dengesizlik: LL -> sag rotasyon]\n", root->key);
        return rotateRight(root);
    }

  
    if (bf < -1 && key > root->right->key) {
        printf("  [%d dugumunde dengesizlik: RR -> sol rotasyon]\n", root->key);
        return rotateLeft(root);
    }

  
    if (bf > 1 && key > root->left->key) {
        printf("  [%d dugumunde dengesizlik: LR -> sol(%d) + sag(%d) rotasyon]\n",
               root->key, root->left->key, root->key);
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    
    if (bf < -1 && key < root->right->key) {
        printf("  [%d dugumunde dengesizlik: RL -> sag(%d) + sol(%d) rotasyon]\n",
               root->key, root->right->key, root->key);
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void preorder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


static void runTest(const char *name, const int *keys, int n) {
    Node *root = NULL;

    printf("Test %s - ekleme sirasi: ", name);
    for (int i = 0; i < n; i++) printf("%d%s", keys[i], i < n - 1 ? ", " : "\n");

    for (int i = 0; i < n; i++)
        root = insertAVL(root, keys[i]);

    printf("  Kok degeri : %d\n", root->key);
    printf("  Preorder   : ");
    preorder(root);
    printf("\n  Inorder    : ");
    inorder(root);
    printf("\n\n");

    freeTree(root);
}

int main(void) {
    int A[] = {30, 20, 10}; 
    int B[] = {10, 20, 30}; 
    int C[] = {30, 10, 20}; 
    int D[] = {10, 30, 20}; 

    runTest("A (LL)", A, 3);
    runTest("B (RR)", B, 3);
    runTest("C (LR)", C, 3);
    runTest("D (RL)", D, 3);

    return 0;
}