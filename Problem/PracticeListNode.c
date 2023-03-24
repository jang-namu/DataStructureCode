#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
    element data;
    struct ListNode *link;  // 자기 참조 구조체 정의 시, 필드 선언ㅇ struct를 붙여줘야 한다.
} ListNode;

// 헤더노드
typedef struct ListType {
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

void error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListType* create() {
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

void insert_first(ListType *plist, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    if (plist->tail == NULL) {
        plist->head = plist->tail = p;
    }
    else {
        p->link = plist->head;
        plist->head = p;
    }
    plist->size++;
}

void insert_last(ListType *plist, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    if (p == NULL) error("메모리 할당 실패");
    p->data = value;
    p->link = NULL;
    if (plist->tail == NULL) {
        plist->head = plist->tail = p;
    }
    else {
        plist->tail->link = p;
        plist->tail = p;
    }
    plist->size++;
}

void print_list(ListType *plist) {
    ListNode *p = plist->head;
    while (p->link != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("%d", p->data);
    printf("\n");
}

int sum_list(ListType *plist) {
    int sum = 0;
    ListNode *p = plist->head;
    while (p != NULL) {
        sum += p->data;
        p = p->link;
    }
    return sum;
}

int count_data(ListType *plist, element value) {
    int count = 0;
    ListNode *p = plist->head;
    while (p != NULL) {
        if (p->data == value) 
            count++;
        p = p->link;
    }
    return count;
}

void delete_data(ListType *plist, element value) {
    ListNode *p, *q;
    p = plist->head;
    q = NULL;
    while (p != NULL) {
        if (p->data == value) {
            if (q == NULL) {
                ListNode *removed = p;
                plist->head = p->link;
                free(removed);
            }
            else {
                ListNode *removed = p;
                q->link = removed->link;
                free(removed);
            }
        }
        q = p;
        p = p->link;
    }
}

int getMax(ListType *plist) {
    ListNode *p = plist->head;
    int max = p->data;
    while (p != NULL) {
        if (p->data > max) 
            max = p->data;
        p = p->link;
    }
    return max;
}

int getMin(ListType *plist) {
    ListNode *p = plist->head;
    int min = p->data;
    while (p != NULL) {
        if (p->data < min) 
            min = p->data;
        p = p->link;
    }
    return min;
}

void alternate(ListType *plist1, ListType *plist2, ListType *plist3) {
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;

    while (a && b) {
        insert_last(plist3, a->data);
        insert_last(plist3, b->data);
        a = a->link;
        b = b->link;
    }

    for (; a; a = a->link) {
        insert_last(plist3, a->data);
    }
    for (; b; b = b->link) {
        insert_last(plist3, b->data);
    }
}

void merge(ListType *plist1, ListType *plist2, ListType *plist3) {
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;

    while (a && b) {
        if (a->data > b->data) {
            insert_last(plist3, b->data);
            b = b->link;
        }
        else if (a->data < b->data) {
            insert_last(plist3, a->data);
            a = a->link;
        }
        else {
            insert_last(plist3, a->data);
            insert_last(plist3, b->data);
            b = b->link;
            a = a->link;
        }
    }

    for (; a; a = a->link) {
        insert_last(plist3, a->data);
    }
    for (; b; b = b->link) {
        insert_last(plist3, b->data);
    }
}

int main(void) {
    ListType *plist = create();

    int n;
    printf("노드의 개수 : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int value;
        printf("노드 #%d 데이터 : ", i);
        scanf("%d", &value);
        insert_last(plist, value);
        print_list(plist);
    }
    printf("연결 리시트 노드의 개수 = %d\n", plist->size);
    printf("연결 리스트의 데이터 합 : %d\n", sum_list(plist));

    int data;
    printf("탐색할 값을 입력하시오 : ");
    scanf("%d", &data);
    printf("%d는 연결 리스트에서 %d번 나타납니다.\n", data, count_data(plist, data));

    delete_data(plist, 5);
    print_list(plist);

    printf("최대값 : %d\n", getMax(plist));
    printf("최소값 : %d\n", getMin(plist));

    ListType *plist2 = create();
    printf("노드의 개수 : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int value;
        printf("노드 #%d 데이터 : ", i);
        scanf("%d", &value);
        insert_last(plist2, value);
    }
    print_list(plist2);

    ListType *plist3 = create();
    alternate(plist, plist2, plist3);
    print_list(plist3);

    ListType *plist4 = create();
    merge(plist, plist2, plist4);
    print_list(plist4);
    
    return 0;
}