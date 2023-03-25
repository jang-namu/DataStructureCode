#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
    int id;
    int avail;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create() {
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h) {
    h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) {
    int i = ++(h->heap_size);   // 주의! h->heap_size++로 작성하면 대입되고 heap_size만 증가함.

    while ((i != 1) && (item.avail < h->heap[i/2].avail)) {
        h->heap[i] = h->heap[i/2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_min_heap(HeapType *h) {
    int parent, child;
    element item, temp;

    temp = h->heap[(h->heap_size)--];
    item = h->heap[1];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].avail > h->heap[child + 1].avail)) {
            child++;
        }
        if (temp.avail < h->heap[child].avail) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

#define JOBS 7
#define MACHINES 3

int main(void) {
    int jobs[JOBS] = { 8, 7, 6, 5, 3, 2, 1 };
    element m = { 0, 0 };
    HeapType* h = create();
    init(h);
    for (int i=0; i<MACHINES; i++) {
        m.id = i + 1;
        m.avail = 0;
        insert_min_heap(h, m);
    }
    for (int i=0; i<JOBS; i++) {
        m = delete_min_heap(h);
        printf("JOB %d을 시간=%d부터 시간=%d까지 기계 %d에 할당한다. \n", i, m.avail, m.avail+jobs[i]-1, m.id);
        m.avail += jobs[i];
        insert_min_heap(h, m);
    }
    return 0;

    return 0;
}