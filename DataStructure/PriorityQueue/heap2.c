#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    int key;
    char ch;
    TreeNode *ptree;
} element;

typedef struct {
    element heap[200];
    int heap_size;
} HeapType;

HeapType* create() {
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h) {
    h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) {
    int i = ++(h->heap_size);

    while((i != 1) && (item.key < h->heap[i/2].key)) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType *h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child+1].key)) {
            child++;
        }
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

TreeNode* make_sub_tree(TreeNode *left, TreeNode *right) {
    TreeNode *new_tree = (TreeNode *)malloc(sizeof(TreeNode));
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

void destroy_tree(TreeNode *root) {
    if (root == NULL) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}

void print_codes(TreeNode *root, int codes[], int top) {
    if (root == NULL) return;
    if (root->left) {
        codes[top] = 1;
        print_codes(root->left, codes, top+1);
    }
    if (root->right) {
        codes[top] = 0;
        print_codes(root->right, codes, top+1);
    }    
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->ch);
        for (int i=0; i < top; i++) {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}


void huffman(char ch_list[], int freq[], int n) {
    element e, e1, e2;
    TreeNode *node, *x;
    HeapType *heap = create();
    init(heap);
    
    for (int i=0; i < n; i++) {
        node = make_sub_tree(NULL, NULL);
        node->key = e.key = freq[i];
        node->ch = e.ch = ch_list[i];
        e.ptree = node;
        insert_min_heap(heap, e);
    }

    for (int i=0; i < n-1; i++) {
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);
        x = make_sub_tree(e1.ptree, e2.ptree);
        e.key = x->key = e1.key + e2.key;
        e.ptree = x;
        insert_min_heap(heap, e);
    }

    int codes[200];
    e = delete_min_heap(heap);
    print_codes(e.ptree, codes, 0);
    destroy_tree(e.ptree);
    free(heap);
}

int main(void) {
    char ch_list[] = { 's', 'i', 'n', 't', 'e'};
    int freq[] = { 4, 6, 8, 12, 15 };
    huffman(ch_list, freq, 5);
    return 0;
}