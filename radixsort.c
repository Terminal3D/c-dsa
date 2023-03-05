#include <stdio.h>
#include <string.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void swap(union Int32* a, union Int32* b) {
    union Int32 temp = *a;
    *a = *b;
    *b = temp;
}

int get_key(union Int32* nums, int c, int i) {
    int key = nums[i].bytes[c];
    if (c == 3) key ^= 128;
    return key;
}

void dSort(union Int32* nums, int c, int n) {
    int count[256];
    memset(count, 0, 256 * sizeof(int));
    for (int i = 0; i < n; i++) {
        int kt = get_key(nums, c, i);
        count[kt]++;
    }
    for (int i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }
    union Int32 sorted[n];
    for (int i = n - 1; i >= 0; i--) {
        int kt = get_key(nums, c, i);
        int index = count[kt] - 1;
        count[kt] = index;
        sorted[index] = nums[i];
    }
    memcpy(nums, sorted, n * sizeof(union Int32));
}

void radixSort(union Int32* nums, int c, int n) {
    for (int i = 0; i < c; i++) {
        dSort(nums, i, n);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    union Int32 nums[n];
    for (int i = 0; i < n; i++) scanf("%d", &nums[i].x);
    radixSort(nums, 4, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i].x);
    }
    printf("\n");
    return 0;
}