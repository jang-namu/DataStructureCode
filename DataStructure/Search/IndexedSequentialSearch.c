#include <stdio.h>
#include <stdlib.h>

int search_index(int key, int n) {
    int i, low, high;
    // 아예 주 리스트 범위에 없으면
    if (key < list[0] || key > list[n-1]) {
        return -1;
    }

    for (i = 0; i < INDEX_SIZE; i++) {
        if (index_list[i].key >= key && index_list[i+1].key < key) {
            break;
        }
    }
    if (i == INDEX_SIZE) {
        low = index_list[INDEX_SIZE-1].index;
        high = n;
    } else {
        low = index_list[i].index;
        high = index_list[i+1].index;
    }
    return seq_search(key, low, high);
}