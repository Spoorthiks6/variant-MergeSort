Merge Sort Variants in C

Merge‑based sorting algorithms: classic merge sort and two‑way merge sort

Merge Sort – Split, sort and merge recursively. O(n log n) time complexity, stable, well-understood algorithm. Standard library routine and the first step in external sorting.
2-way Natural Merge - Identifies sorted sequences and only merges consecutive sequences. Adaptive to partially sorted sequences; performs better when input is nearly sorted (logs, time series).

Compilation & Execution

```bash
gcc mergeSort.c -o mergeSort && ./mergeSort
gcc twoWayMerge.c -o twoWayMerge && ./twoWayMerge
