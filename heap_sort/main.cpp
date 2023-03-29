#include <iostream>
using std::cout, std::endl, std::swap;

void transformToMaxHeap(int arr[], int N, int i) {
    int largest = i;
    int l = (2*i) + 1;
    int r = (2*i) + 2;

    if (l<N && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r<N && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        //  1
        // 2 3
        // get largest from this subtree, and get max number to the top
        swap(arr[i], arr[largest]);
        transformToMaxHeap(arr, N ,largest);
    }
}

void heapSort(int arr[], int N) {
    for (int i = N/2 - 1; i >= 0; i--)
        transformToMaxHeap(arr, N, i);

    for (int i=N-1; i>0; i--) {

        swap(arr[0], arr[i]); 
        transformToMaxHeap(arr, i, 0);
    }
}

void printArray(int arr[], int N) {
    for(int i=0; i<N; i++) {
        cout<<arr[i]<<" ";
    }
}

int main() {
    int arr[5] = {1, 3, 2, 5 ,4};
    heapSort(arr, 5);
    printArray(arr, 5);
    return 0;
}