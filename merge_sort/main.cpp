#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int arrOne = mid-left+1;
    int arrTwo = right-mid;

    int* leftArr = new int[arrOne];
    int* rightArr = new int[arrTwo];

    for (int i = 0; i < arrOne; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < arrTwo; j++)
        rightArr[j] = arr[mid + 1 + j];

    int indexOfSubArrayOne = 0,
        indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left; 
    
    while (indexOfSubArrayOne < arrOne
           && indexOfSubArrayTwo < arrTwo) {
        if (leftArr[indexOfSubArrayOne] <= rightArr[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray]= leftArr[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArr[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < arrOne) {
        arr[indexOfMergedArray] = leftArr[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < arrTwo) {
        arr[indexOfMergedArray] = rightArr[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void merge_sort(int arr[], int begin, int end) {
    if(begin >= end) {
        return;
    }
    auto mid = (begin + end) / 2;
    merge_sort(arr, begin, mid);
    merge_sort(arr, mid+1, end);
    merge(arr, begin, mid, end);
}

void printArray(int arr[], int N) {
    for(int i=0; i<N; i++) {
        cout<<arr[i]<<" ";
    }
}

int main() {
    int arr[5] = {1, 3, 2, 5 ,4};
    merge_sort(arr, 0 ,5);
    printArray(arr, 5);
    return 0;
}