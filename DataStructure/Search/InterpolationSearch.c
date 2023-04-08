#include <stdio.h>
#include <stdlib.h>

int interpolation_search(int list[], int key, int n) {
    int low, high, j;
    low = 0;
    high = n-1;
    while ((list[high] >= key) && (list[low] < key)) {
        j = ((float)(key-list[low])) / (list[high]-list[low]) * (high - low) + low; // + low는 처음 탐색 위치.
        if (key > list[j]) low = j+1;
        else if (key < list[j]) high = j-1;
        else low = j;
    }
    if (list[low] == key) return low;
    else return -1;
}