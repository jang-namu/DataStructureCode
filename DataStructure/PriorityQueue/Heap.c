#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define MAX_ELEMENT_SIZE 100

typedef struct {
    int key;
} element;
typedef struct {
    element heap[MAX_ELEMENT_SIZE];
    int heap_size;
} HeapType;

HeapType* create() {
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h) {
    h->heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) {
    int i = ++h->heap_size;
    h->heap[i] = item;
    
    // 트리를 거슬러 올라가며 부모 노드와 비교.
    while ((i != 1) && (item.key > h->heap[i/2].key)) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType *h) {
    int parent, child;
    element item, temp;
    
    parent = 1;
    child = 2;
    item = h->heap[1];
    temp = h->heap[h->heap_size--];

    while (child <= h->heap_size) {
        // 현재 노드의 자식 노드 중 더 큰 자식 노드를 찾는다.
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }
        // 현재 노드가 두 개의 자식 보다 크면 break
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void heap_sort(element a[], int n) {
    int i;
    HeapType *h;

    h = create();
    init(h);
    
    for (int i=0; i < n; i++) {
        insert_max_heap(h, a[i]);
    }
    for (int i = n-1; i >= 0; i--) {
        a[i] = delete_max_heap(h);
    }
    free(h);
}

int main(void) {
    element e1 = {10}, e2 = {5}, e3 = {30};
    element e4, e5, e6;
    HeapType *heap;

    heap = create();
    init(heap);

    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);

    e4 = delete_max_heap(heap);
    printf("< %d >", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %d >", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d >\n>", e6.key);
    
    free(heap);

    element list[SIZE] = { 23, 56, 11, 9, 56, 99, 27, 34 };
    heap_sort(list, SIZE);
    for (int i=0; i < SIZE; i++) {
        printf("%d ", list[i].key);
    }
    printf("\n");
    return 0;
}