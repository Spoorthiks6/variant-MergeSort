#include <stdio.h>
#include <stdlib.h>

int findRun(int arr[], int start, int n) {
    int end = start;
    while (end + 1 < n && arr[end] <= arr[end + 1]) {
        end++;
    }
    return end;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void TwoWayMergeSort(int arr[], int n) {
    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        int left = 0;
        while (left < n - 1) {
            int mid = findRun(arr, left, n);       
            if (mid == n - 1) break;                
            int right = findRun(arr, mid + 1, n);   
            merge(arr, left, mid, right);
            sorted = 0;                            
            left = right + 1;                     
        }
    }
}

int main() {
    int arr[] = {3, 8, 15, 2, 9, 20, 1, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    TwoWayMergeSort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}