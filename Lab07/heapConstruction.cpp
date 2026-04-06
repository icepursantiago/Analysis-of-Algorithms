#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Heapify function
void heapify(vector<int>& A, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && A[left] > A[largest]) {
        largest = left;
    }
    
    if (right < n && A[right] > A[largest]) {
        largest = right;
    }
    
    if (largest != i) {
        swap(A[i], A[largest]);
        heapify(A, largest, n);
    }
}

// Build heap from array
void buildHeap(vector<int>& A) {
    int n = A.size();
    
    // Start from last non-leaf node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, i, n);
    }
}

// Print array
void printArray(const vector<int>& A) {
    for (int val : A) {
        cout << setw(4) << val << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int n = 10;
    vector<int> A(n);
    
    // Generate random array
    cout << "Random array:" << endl;
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
    printArray(A);
    
    // Build heap
    buildHeap(A);
    
    cout << "\nHeap after construction:" << endl;
    printArray(A);
    
    // Verify heap property
    cout << "\nHeap verification (parent >= children):" << endl;
    bool valid = true;
    for (int i = 0; i < n / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if ((left < n && A[i] < A[left]) || (right < n && A[i] < A[right])) {
            valid = false;
            cout << "Invalid heap property at index " << i << endl;
        }
    }
    if (valid) {
        cout << "Heap property is satisfied!" << endl;
    }
    
    return 0;
}