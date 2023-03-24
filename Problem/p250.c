// 250p의 3번과 4번을 구현해보자.
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct CircularLinkedList {
    element data;
    struct CircularLinkedList *link;
} CircularLinkedList;

CircularLinkedList* insert_first(CircularLinkedList *head, element item) {
    CircularLinkedList *newnode = (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
    newnode->data = item;
    if (head == NULL) {
        head = newnode;
        head->link = head;
    }
    else {
        newnode->link = head->link;
        head->link = newnode;
    }
    return head;
}

CircularLinkedList* insert_last(CircularLinkedList *head, element item) { 
    // head를 동적할당받지 않으므로 헤드를 바꾸려면 return해서 대입해줘야한다.
    CircularLinkedList *newnode = (CircularLinkedList *)malloc(sizeof(CircularLinkedList));
    newnode->data = item;
    if (head == NULL) {
        head = newnode;
        head->link = head;
    }
    else {
        newnode->link = head->link;
        head->link = newnode;
        head = newnode;
    }
    return head;
}

void print_CircularLinkedList(CircularLinkedList *head) {
    if (head == NULL) return;
    CircularLinkedList *p;
    for (p = head->link; p != head; p = p->link) {
        printf("%d->", p->data);
    }
    printf("%d\n", p->data);
}

CircularLinkedList* search(CircularLinkedList *head, element data) {
    if (head == NULL) return NULL;
    CircularLinkedList *p = head->link;
    for (p = head->link; p != head; p = p->link) {
        if (p->data == data) {
            return p;
        }
    }
    if (p->data == data) {
        return p;
    }
    else {
        return NULL;
    }
}

int get_size(CircularLinkedList *head) {
    if (head == NULL) return 0;
    CircularLinkedList *p;
    int count = 1;
    for (p = head->link; p != head; p = p->link) {
        count++;
    }
    return count;
}

int main(void) {
    CircularLinkedList *c = NULL;   // c는 동적할당 받은게 아님.
    //printf("%d\n", get_size(c));
    //print_CircularLinkedList(c);
    for (int i = 1; i < 8; i++) {
        c = insert_first(c, i);
    }
    printf("%d\n", get_size(c));
    print_CircularLinkedList(c);
    CircularLinkedList *seven = search(c, 4);
    printf("%d\n", seven->data);
    return 0;
}