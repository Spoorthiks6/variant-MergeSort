#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;    
    int run_idx;  
    int next;     
} HeapNode;

void heapify_down(HeapNode heap[], int size, int i) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left  < size && heap[left].value  < heap[smallest].value) smallest = left;
    if (right < size && heap[right].value < heap[smallest].value) smallest = right;

    if (smallest != i) {
        HeapNode tmp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = tmp;
        heapify_down(heap, size, smallest);
    }
}

void build_min_heap(HeapNode heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify_down(heap, size, i);
}


void sort_chunk(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void kway_merge_sort(int arr[], int n, int k) {
    int chunk = (n + k - 1) / k;   

    for (int i = 0; i < k; i++) {
        int left  = i * chunk;
        int right = (left + chunk - 1 < n) ? left + chunk - 1 : n - 1;
        if (left < n)
            sort_chunk(arr, left, right);
    }

    int   *starts = malloc(k * sizeof(int));
    int   *ends   = malloc(k * sizeof(int));
    int   *output = malloc(n * sizeof(int));
    HeapNode *heap = malloc(k * sizeof(HeapNode));

    int heap_size = 0;
    for (int i = 0; i < k; i++) {
        starts[i] = i * chunk;
        ends[i]   = (starts[i] + chunk - 1 < n) ? starts[i] + chunk - 1 : n - 1;
        if (starts[i] < n) {
            heap[heap_size].value   = arr[starts[i]];
            heap[heap_size].run_idx = i;
            heap[heap_size].next    = starts[i] + 1;
            heap_size++;
        }
    }
    build_min_heap(heap, heap_size);

    int out = 0;
    while (heap_size > 0) {
        HeapNode min = heap[0];
        output[out++] = min.value;

        int r = min.run_idx;
        if (min.next <= ends[r]) {

            heap[0].value   = arr[min.next];
            heap[0].run_idx = r;          
            heap[0].next    = min.next + 1;
        } else {
           
            heap[0] = heap[--heap_size];
        }
        heapify_down(heap, heap_size, 0);
    }

   
    for (int i = 0; i < n; i++) arr[i] = output[i];

    free(starts); free(ends); free(output); free(heap);
}

int main() {
    int arr[] = {3, 18, 15, 2, 39, 20, 1, 47};
    int n = sizeof(arr) / sizeof(arr[0]);
    kway_merge_sort(arr, n, 2);
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}