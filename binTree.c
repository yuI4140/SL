#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = (Node*) malloc(sizeof(Node));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    } else {
        if (value < (*root)->value) {
            insert(&((*root)->left), value);
        } else {
            insert(&((*root)->right), value);
        }
    }
}

void traverseInOrder(Node* root) {
    if (root != NULL) {
        traverseInOrder(root->left);
        printf("%d ", root->value);
        traverseInOrder(root->right);
    }
}
Node* find(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    } else if (value < root->value) {
        return find(root->left, value);
    } else if (value > root->value) {
        return find(root->right, value);
    } else {
        return root;
    }
}

void remove(Node** root, int value) {
    if (*root == NULL) {
        return;
    }
    if (value < (*root)->value) {
        remove(&((*root)->left), value);
    } else if (value > (*root)->value) {
        remove(&((*root)->right), value);
    } else {
        Node* temp;
        if ((*root)->left == NULL) {
            temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            temp = findMin((*root)->right);
            (*root)->value = temp->value;
            remove(&((*root)->right), temp->value);
        }
    }
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* findMax(Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int isBST(Node* root) {
    if (root == NULL) {
        return 1;
    }
    if (root->left != NULL && root->left->value > root->value) {
        return 0;
    }
    if (root->right != NULL && root->right->value < root->value) {
        return 0;
    }
    if (!isBST(root->left) || !isBST(root->right)) {
        return 0;
    }
    return 1;
}

Node* createNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertIter(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    Node* node = root;
    while (1) {
        if (value < node->value) {
            if (node->left == NULL) {
                node->left = createNode(value);
                return root;
            } else {
                node = node->left;
            }
        } else if (value > node->value) {
            if (node->right == NULL) {
                node->right = createNode(value);
                return root;
            } else {
                node = node->right;
            }
        } else {
            return root;
        }
    }
}

void traversePreOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        traversePreOrder(root->left);
        traversePreOrder(root->right);
    }
}

void traverseInOrder(Node* root) {
    if (root != NULL) {
        traverseInOrder(root->left);
        printf("%d ", root->value);
        traverseInOrder(root->right);
    }
}

void traversePostOrder(Node* root) {
    if (root != NULL) {
        traversePostOrder(root->left);
        traversePostOrder(root->right);
        printf("%d ", root->value);
}
