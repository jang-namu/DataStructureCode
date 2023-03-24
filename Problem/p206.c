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

ListNode* reverse(ListNode *head) {
    ListNode *p, *q, *r;
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
    head = (ListNode *)malloc(sizeof(ListNode));
    head->data = 1;

    ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
    new_node->data = 2;
    new_node->link = NULL;
    head->link = new_node;
    
    print_list(head);

    head = insert_first(head, 3);
    print_list(head);

    head = insert(head, new_node, 40);
    head = insert(head, head->link, 20);
    print_list(head);

    head = delete_first(head);
    print_list(head);

    head = delete(head, head->link);
    print_list(head);
    
    element tmp = get_entry(head, 3);
    printf("%d\n", tmp);
    print_list(head);
    printf("%d\n", get_length(head));

    return 0;
}