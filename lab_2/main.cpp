#include <iostream>
#include <string>
using namespace std;

bool compare(string a, string b) {
    if (a.size() == b.size()) {
        for (int i = 0; i < a.length(); i++) {
            if ((a[i] ) < (b[i] )) {
                return false;
            } else if(a[i]> b[i]){
                return true;
            }
        }
        return false;
    }
    else {
        if(a.size()>b.size()) return true;
        return false;
    }
}

template <typename T> void printArray(T* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << endl;
    }
}

void heapify_max(std::string* arr, int n, int i) {
    int currentLargest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < n && compare(arr[left], arr[currentLargest])) {
        currentLargest = left;
    }

    if (right < n && compare(arr[right], arr[currentLargest])) {
        currentLargest = right;
    }

    if (currentLargest != i) {
        swap(arr[i], arr[currentLargest]);
        heapify_max(arr, n, currentLargest);
    }
}



void heap_sort(std::string* arr, int n) {
    for (int i = n-1; i >= 0; i--) {
        heapify_max(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify_max(arr, i, 0);
    }
}



int main() {
    int n;
    cin >> n;
    string* arr = new string[n];

    for(int i=0; i<n; i++) {
        cin >>arr[i];
    }
    heap_sort(arr, n);
    printArray(arr, n);
    delete[] arr;
    return 0;
}