#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DListNode {
    element data;
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

void init(DListNode *phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode *phead, DListNode *current) {
    DListNode *p;
    printf("\n");
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current) {
            printf("<-| #%s# |->", p->data);
        }
        else {
            printf("<-| %s |->", p->data);
        }
    }
    printf("\n");
}

void dinsert(DListNode *before, element data) {
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    strcpy(newnode->data, data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DListNode *phead, DListNode *removed) {
    if (phead == removed) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main(void) {
    char ch;
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));
    
    init(head);

    dinsert(head, "The blue stones");
    dinsert(head, "Purple");
    dinsert(head, "Oasis");

    DListNode *current = head->rlink;
    print_dlist(head, current);

    do {
        printf("\n 명령어를 입력하시오 (<, >, q): ");
        ch = getchar();
        if (ch == '<') {
            current = current->llink;
            if (current == head) {
                current = current->llink;
            }
        }
        else if (ch == '>') {
            current = current->rlink;
            if (current == head) {
                current = current->rlink;
            }
        }
        print_dlist(head, current);
        getchar();
    } while(ch != 'q');

    while (head->rlink != head) {
        ddelete(head, head->rlink);
    }

    free(head);
    free(current);
    return 0;
}