#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;  // 자기 참조 구조체
} ListNode;

void error(char *str) {
    fprintf(stderr, "%s", str);
    exit(0);
}


void print_list(ListNode *head) {    
    // 조건식에 p->link != NULL가 아닌 p != NULL을 쓴다.
    // 생각해보면 link는 다음 노드의 링크가 아닌, 노드 자체의 주소를 가리키기 때문이다.
    for (ListNode *p = head; p != NULL; p = p->link) {
        printf("%d ->", p->data);
    }
    printf("NULL \n");
}


ListNode* insert_first(ListNode *head, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head; // 헤드 포인터의 값을 복사
    head = p;   // 헤드 포인터 변경
    return head;    // 변경된 헤드 포인터 반환
}


ListNode* insert(ListNode *head, ListNode *pre, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value; 
    p->link = pre->link;    // 이전 노드의 링크를 새로운 노드으 링크에 저장
    pre->link = p;  // pre의 link를 새 노드인 p로 업데이트
    return head;    // 헤드를 반환
}


ListNode* delete_first(ListNode *head) {
    ListNode *removed;
    if (head == NULL) return NULL;
    removed = head; // 헤드 포인터의 값을 removed에 복사한다.
    head = removed->link;   // 헤드 포인터의 값을 (원래)head->link로 변경한다.
    free(removed); // removed의 동적 메모리를 반환한다.
    return head;    // 바뀐 헤드를 반환한다.
}

ListNode* delete(ListNode *head, ListNode *pre) {
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}


element get_entry(ListNode *head, int index) {
    if (index <= 0) error("out of index");
    ListNode *p = head;
    for (int i = 1; i < index; i++) {
        if (p == NULL) error("out of index");
        p = p->link;
    }
    return p->data;
}

int get_length(ListNode *head) {
    int length = 0;
    for (ListNode *p=head; p != NULL; p = p->link) {
        length++;
    }
    return length;
}

ListNode* search_list(ListNode *head, element x) {
    ListNode *p = head;

    while (p != NULL) {
        if (p->data == x) {
            return p;
        }
        p = p->link;
    }
    return NULL;
}

ListNode* concat_list(ListNode *head1, ListNode *head2) {
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    
    ListNode *p = head1;
    while(p->link != NULL) {
        p = p->link;
    }
    p->link = head2;
    return head1;
}

ListNode* reverse(ListNode *head) { 
    ListNode *p, *q, *r;    // 새로운 연결리스트를 만들지 않고 포인터만 사용
    p = head;
    q = NULL;
    while (p != NULL) {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    return q;
}


int main(void) {
    ListNode *head = NULL;
    ListNode *head2 = NULL;
    head = insert_first(head, 10);
    head = insert_first(head, 20);
    head = insert_first(head, 30);
    print_list(head);

    head2 = insert_first(head2, 40);
    head2 = insert_first(head2, 50);
    head2 = insert_first(head2, 60);
    print_list(head2);

    if (search_list(head, 30) != NULL) {
        printf("리스트에서 30을 찾았습니다. \n");
    }
    else {
        printf("리스트에서 30을 찾지 못 했습니다. \n");
    }

    ListNode *total = concat_list(head, head2);
    print_list(total);

    total = reverse(total);
    print_list(total);
    
    return 0;
}