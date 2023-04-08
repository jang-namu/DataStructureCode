#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b)  (((a) > (b)) ? (a) : (b))

typedef int element;
typedef struct AVLNode {
    element data;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

int get_height(AVLNode *node) {
    int height = 0;
    if (node != NULL) {
        height = 1 + MAX(get_height(node->left), get_height(node->right));
    }
    return height;
}

int get_balance(AVLNode *node) {
    if (node == NULL) return 0;
    return get_height(node->left) - get_height(node->right);
}

AVLNode* rotate_right(AVLNode *parent) {
    AVLNode *child = parent->left;
    parent->left = child->right;
    child->right = parent;
    return child;   // 새로운 루트를 반환
}

AVLNode* rotate_left(AVLNode *parent) {
    AVLNode *child = parent->right;
    parent->right = child->left;
    child->left = parent;
    return child;
}

AVLNode* create_node(int key) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->data = key;
    node->left = node->right = NULL;
    return node;
}

AVLNode* insert(AVLNode* node, int key) {
    if (node == NULL) return create_node(key);

    if (key > node->data) {
        node->right = insert(node->right, key);
    } else if (key < node->data) {
        node->left = insert(node->left, key);
    } else {
        return node;    // 이진탐색트리는 key 중복을 허용하지 않는다.
    }

    int balance = get_balance(node);

    // LL
    if (balance > 1 && (node->left->data > key)) {
        return rotate_right(node);
    } 
    // LR
    if (balance > 1 && (node->left->data < key)) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    // RR
    if (balance < -1 && (node->right->data < key)) {
        return rotate_left(node);
    }
    // RL
    if (balance < -1 && (node->right->data > key)) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

AVLNode* delete(AVLNode *node, int key) {
    if (node==NULL) return node;
    
    if (node->data > key) {
        node->left = delete(node->left, key);
    } else if (node->data < key) {
        node->right = delete(node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if (node->left == NULL || node->right == NULL) {
            AVLNode *temp = node->left ? node->left : node->right;
            free(node);
            return temp;
        } else {
            AVLNode *successor_node = node->right;
            while (successor_node->left != NULL) {
                successor_node = successor_node->left;
            }
            node->data = successor_node->data;
            node->right = delete(node->right, successor_node->data);
        }
    }

    int balance = get_balance(node);

    // LL
    if (balance > 1 && get_balance(node->left) >= 0) {
        return rotate_right(node);
    } 
    // LR
    if (balance > 1 && get_balance(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    } 
    // RR
    if (balance < -1 && get_balance(node->right) <= 0) {
        return rotate_left(node);
    } 
    // RL
    if (balance < -1 && get_balance(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node; 
}

void preorder(AVLNode *root) {
    if (root != NULL) {
        printf("[%d] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main(void) {
    AVLNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 29);

    printf("전위 순회 결과 \n");
    preorder(root);
    printf("\n");
    
    root = delete(root, 40);
    root = delete(root, 50);
    printf("전위 순회 결과 \n");
    preorder(root);
    printf("\n");
    return 0;
}