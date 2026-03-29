#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void merge_arrays(int arr[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for(int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for(int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void merge_sort(int arr[], int left, int right){
    if(left >= right) return;

    int mid = left + (right - left) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge_arrays(arr, left, mid, right);
}

void print_array(int arr[], int n){
    for(int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;
}

int main(){
    srand(time(0));

    int n;
    cout << "Enter array size: ";
    cin >> n;

    if(n < 1 || n > 200000){
        cout << "Enter 1..200000" << endl;
        return 1;
    }

    int *arr = new int[n];
    for(int i = 0; i < n; ++i){
        arr[i] = rand() % 100;
    }

    cout << "\nUnsorted:\n";
    if(n <= 50) print_array(arr, n);

    merge_sort(arr, 0, n - 1);

    cout << "\nSorted:\n";
    if(n <= 50) print_array(arr, n);

    delete[] arr;
    return 0;
}