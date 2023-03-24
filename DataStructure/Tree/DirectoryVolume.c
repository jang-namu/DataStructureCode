#include <stdio.h>
#include <stdlib.h>
#define MAX(i, j) ((i > j) ? i : j)

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

void init(TreeNode *self, int data, TreeNode *left, TreeNode *right) {
    self->data = data;
    self->left = left;
    self->right = right;
}

int calc_dir_size(TreeNode *root) {
    if (root == NULL) return 0;
    return calc_dir_size(root->left) + calc_dir_size(root->right) + root->data;
}

int get_node_count(TreeNode *root) {
    if (root == NULL) return 0;
    return get_node_count(root->left) + get_node_count(root->right) + 1;
}

int get_leaf_count(TreeNode *root) {
    int count = 0;

    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            return 1;
        } else {
            count = get_leaf_count(root->left) + get_leaf_count(root->right);
        }
    }
    return count;
}

int get_height(TreeNode *root) {
    int height = 0;

    if (root != NULL) {
        height = 1 + MAX(get_height(root->left), get_height(root->right));
    }

    return height;
}

int equal(TreeNode *t1, TreeNode *t2) {
    if (t1 == NULL && t2 == NULL) {
        return 1;
    }
    if ((t1 == NULL && t2 != NULL) || (t1 != NULL && t2 == NULL)) {
        return 0;
    }
    if (t1->data != t2->data) {
        return 0;
    } else if (equal(t1->left, t2->left) && equal(t1->right, t2->right)) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    TreeNode *n4 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n5 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n3 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n2 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n1 = (TreeNode *)malloc(sizeof(TreeNode));

    init(n4, 500, NULL, NULL);
    init(n5, 200, NULL, NULL);
    init(n3, 100, n4, n5);
    init(n2, 50, NULL, NULL);
    init(n1, 0, n2, n3);


    TreeNode *n14 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n15 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n13 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n12 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n11 = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *n20 = (TreeNode *)malloc(sizeof(TreeNode));

    init(n14, 500, NULL, NULL);
    init(n15, 200, NULL, NULL);
    init(n13, 100, n14, n15);
    init(n12, 50, NULL, NULL);
    init(n11, 0, n12, n13);
    init(n20, 33, NULL, NULL);


    printf("디렉토리의 크기=%d\n", calc_dir_size(n1));
    printf("노드의 개수=%d\n", get_node_count(n1));
    printf("단말노드의 개수=%d\n", get_leaf_count(n1));
    printf("트리의 높이=%d\n", get_height(n1));
    printf("%d\n", equal(n1, n11));
}