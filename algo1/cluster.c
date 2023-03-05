#include <stdio.h>
#include <stdlib.h>


void swap(int *arr, int i, int j);
void heapify(int *arr, int i, int n);
void read_items(int num_items, int *items);
int get_max_time(int num_items, int max_num_items, int *items);

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int main() {
    int num_items, max_num_items;
    scanf("%d%d", &num_items, &max_num_items);
    int *items = calloc(num_items, sizeof(int));
    read_items(num_items, items);
    int max_time = get_max_time(num_items, max_num_items, items);
    printf("%d\n", max_time);
    free(items);
    return 0;
}

void read_items(int num_items, int *items) {
    for (int i = 0; i < num_items; i++) {
        int start_time, end_time;
        scanf("%d %d", &start_time, &end_time);
        items[i] = start_time + end_time;
    }
    for (int i = num_items / 2 - 1; i >= 0; i--) {
        heapify(items, i, num_items);
    }
}

int get_max_time(int num_items, int max_num_items, int *items) {
    int count = num_items;
    for (int i = num_items; i < max_num_items; i++) {
        int start_time, end_time;
        scanf("%d %d", &start_time, &end_time);
        start_time = max(start_time, items[0]);
        if (--count > 0) {
            items[0] = items[count];
            heapify(items, 0, count);
        }
        int t = count++;
        items[t] = end_time + start_time;
        while (t > 0 && items[t] < items[(t - 1) / 2]) {
            swap(items, (t - 1) / 2, t);
            t = (t - 1) / 2;
        }
    }
    int max_time = num_items != 0 ? items[0] : 0;
    for (int i = 1; i < num_items; i++) {
        if (items[i] > max_time) {
            max_time = items[i];
        }
    }
    return max_time;
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(int *arr, int i, int n) {
    int left_child = 2 * i + 1;
    int right_child = left_child + 1;
    int index = i;
    if (left_child < n && arr[left_child] < arr[i]) index = left_child;
    if (right_child < n && arr[right_child] < arr[index]) index = right_child;
    if (index == i) return;
    swap(arr, index, i);
    heapify(arr, index, n);
}
