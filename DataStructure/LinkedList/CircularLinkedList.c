#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;  // 자기 참조 구조체 (struct에 주의!)
} ListNode;

ListNode* insert_first(ListNode *head, element data) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = data;
    if (head == NULL) {
        head = p;
        p->link = head;
    }
    else {
        p->link = head->link;
        head->link = p;
    }
    return head;
}

ListNode* insert_last(ListNode *head, element data) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = data;
    if (head == NULL) {
        head = p;
        p->link = head;
    }
    else {
        p->link = head->link;
        head->link = p;
        head = p;
    }
    return head;
 }

void print_list(ListNode *head) {
    ListNode *p;
    p = head->link;
    do {
        printf("%d->", p->data);
        p = p->link;
    } while (p != head);
    printf("%d\n", p->data);
}



int main(void) {
    ListNode *p = NULL;

    p = insert_last(p, 20);
    p = insert_last(p, 30);
    p = insert_last(p, 40);
    p = insert_first(p, 10);
    print_list(p);
    
    return 0;
}