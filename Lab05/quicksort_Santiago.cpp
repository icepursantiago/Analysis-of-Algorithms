#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int partition_array(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j <= high - 1; ++j){
        if(arr[j] <= pivot){
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }

    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}

void quick_sort(int arr[], int low, int high){
    if(low < high){
        int pi = partition_array(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
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

    if(n < 1 || n > 2000000){
        cout << "Enter 1..2000000" << endl;
        return 1;
    }

    int *arr = new int[n];
    for(int i = 0; i < n; ++i){
        arr[i] = rand();
    }

    cout << "\nUnsorted:\n";
    if(n <= 50) print_array(arr, n);

    auto t_start = chrono::high_resolution_clock::now();
    quick_sort(arr, 0, n - 1);
    auto t_finish = chrono::high_resolution_clock::now();

    cout << "\nSorted:\n";
    if(n <= 50) print_array(arr, n);

    double elapsed = chrono::duration<double, milli>(t_finish - t_start).count();
    cout << "\nQuick Sort time: " << elapsed << " ms" << endl;

    delete[] arr;
    return 0;
}
