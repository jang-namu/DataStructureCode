#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;


void init(DListNode *head) {
    head->llink = head;
    head->rlink = head;
}

void insert(DListNode *before, element data) {
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DListNode *head, DListNode *removed) {
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void print_DListNode_reverse(DListNode *head) {
    DListNode *p = head->llink;
    for (; p != head; p = p->llink) {
        printf("%d ", p->data);
    }
    printf("\n");
}

DListNode* search(DListNode *head, element data) {
    DListNode *p = head->llink;
    for (; p != head; p = p->llink) {
        if (p->data == data) {
            return p;
        }
    }
    return NULL;
} 

int main(void) {
    int n, data;
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));
    init(head);

    printf("데이터의 개수를 입력하시오 : ");
    scanf("%d", &n);

    for (int i = 1; i < n+1; i++) {
        printf("노드 #%d의 데이터를 입력하시오: ", i);
        scanf("%d", &data);
        insert_last(head, data);
    }
    
    DListNode *tmp = search(head, 7);
    printf("%d\n", tmp->data);
    print_DListNode_reverse(head);
}



