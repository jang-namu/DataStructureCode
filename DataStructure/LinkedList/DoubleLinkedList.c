#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

void init(DlistNode *phead) {   // void에 유의, 이중 연결리스트는 사용전에 반드시 초기화!
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DlistNode *before, element data)  
{
    // 만약! 헤드노드가 존재하지 않는다면??
    // 처음 노드를 추가할 경우를 대비해서 if문을 사용해, head 포인터가 null인지 확인해야함.
    DlistNode *newnode = (DlistNode *)malloc(sizeof(DlistNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DlistNode *head, DlistNode *removed) {
    // 만약! 헤드노드가 존재하지 않는다면??
    // 처음 노드를 추가할 경우를 대비해서 if문을 사용해, head 포인터가 null인지 확인해야함.
    if (head == removed) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void print_dlist(DlistNode *phead) {
    DlistNode *p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        printf("<-| |%d| |->", p->data);
    }
    printf("\n");
}


int main(void) {
    DlistNode *head = (DlistNode *)malloc(sizeof(DlistNode));   // 헤드 노드는 포인터 변수가 아닌 구조체 변수!
    init(head);
    printf("추가 단계\n");
    for (int i = 0; i < 5; i++) {
        // 헤드 노드의 오르쪽 삽입
        dinsert(head, i);
        print_dlist(head);
    }
    
    printf("\n삭제단계\n");
    for (int i = 0; i < 5; i++) {
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    free(head);

    return 0;
}