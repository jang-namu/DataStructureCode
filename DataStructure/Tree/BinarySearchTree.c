#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct TreeNode {
    element key;
    struct TreeNode *left, *right;
} TreeNode;

/* 탐색 연산(순환)
TreeNode* search(TreeNode *root, int key) {
    if (root == NULL) return NULL;
    if (key == root->key) return root;
    else if (key < root->key) return search(root->left, key);
    else return search(root->right, key);
}*/

TreeNode* search(TreeNode *root, int key) {
    TreeNode *p = root;
    while (p) {
        if (key == p->key) {
            return p;
        } else if(key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return NULL;
}

TreeNode* new_node(int item) {
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    new_node->key = item;
    new_node->left = new_node->right = NULL;
    return new_node;
}

TreeNode* insert_node(TreeNode *root, int key) {
    // 트리가 공백이면 새로운 노드를 반환한다.
    if (root == NULL) {
        return new_node(key);
    } 
    // 그렇지 않으면, 순환적으로 트리를 내려간다.
    if (key < root->key) {
        root->left = insert_node(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key);
    }
    return root;
}

TreeNode* delete_node(TreeNode *root, int key) {
    // 트리가 공백 상태이면 삭제할게 없다.
    if (root == NULL) return root;
    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        // 1, 2번의 경우 (1번 : 삭제하려는 노드가 단말 노드, 2번 : 삭제하려는 노드가 왼쪽, 오른쪽 중 하나의 서브트리만 가짐)
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        } else {
            // 3번째 경우(양쪽 서브트리를 다 가질 때)
            TreeNode *temp = root->right;   // 오른쪽 후계자를 선택.
            while (temp->left) {            // 루트와 가장 가까운 값.
                temp = temp->left;
            }
            // 중위 순회 시, 후계 노드를 복사한다.
            root->key = temp->key;
            // 중위 순회 시, 후계 노드를 삭제한다. 이 delete_node에서 삭제할 노드는 단말노드이거나 오른쪽 서브트리를 갖는다.
            root->right = delete_node(root->right, temp->key);  // 오른쪽에서 찾아서 삭제
        }
    }
    return root;
}

void inorder(TreeNode *root) {
    if (root) {
        inorder(root->left);
        printf("[%d] ", root->key);
        inorder(root->right);
    }
}

int main(void) {
    TreeNode *root = NULL;
    TreeNode *tmp = NULL;

    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);

    printf("이진 탐색 트리 중위 순회 결과\n");
    inorder(root);
    printf("\n\n");
    if (search(root, 30) != NULL)
        printf("이진 탐색  트리에서 30을 발견\n");
    else
        printf("이진 탐색  트리에서 30을 발견 못 함\n");
    printf("\n");

    root = delete_node(root, 50);
    inorder(root);
    printf("\n\n");

    root = insert_node(root, 25);
    inorder(root);
    printf("\n\n");

    root = delete_node(root, 20);
    inorder(root);
    printf("\n\n");
}