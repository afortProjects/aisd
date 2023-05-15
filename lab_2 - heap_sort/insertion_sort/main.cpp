#include <iostream>
using namespace std;


void insertionSort(int arr[], int n) {
    for(int i=0; i<n; i++) {
        int j = i;
        while (j>0 && arr[j-1] > arr[j]) {
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
}

void printArray(int arr[], int N) {
    for(int i=0; i<N; i++) {
        cout<<arr[i]<<" ";
    }
}

int main() {
    int arr[7] = {1, 3, 2, 5 ,4, 123123 ,123123};
    insertionSort(arr, 7);
    printArray(arr, 7);
    return 0;
}