#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

int binary_search(int arr[], int n, int key){
    int low = 0, high = n - 1;

    while(low <= high){
        int mid = low + (high - low) / 2;

        if(arr[mid] == key) return mid;
        if(arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int interpolation_search(int arr[], int n, int key){
    int low = 0, high = n - 1;

    while(low <= high && key >= arr[low] && key <= arr[high]){
        if(arr[high] == arr[low]){
            if(arr[low] == key) return low;
            else return -1;
        }

        long long pos = low + (long long)(high - low) * (key - arr[low]) / (arr[high] - arr[low]);

        if(pos < low || pos > high) return -1;

        if(arr[pos] == key) return (int)pos;
        if(arr[pos] < key) low = (int)pos + 1;
        else high = (int)pos - 1;
    }
    return -1;
}

int main(){
    srand(time(0));

    const int n = 10000000;
    int *arr = new int[n];

    cout << "Generating " << n << " random numbers (sorted sequence)...\n";

    int current = 0;
    for(int i = 0; i < n; ++i){
        current += rand() % 3;
        arr[i] = current;
    }

    int key;
    cout << "Enter key to search: ";
    cin >> key;

    auto t_start = chrono::high_resolution_clock::now();
    int idx_bin = binary_search(arr, n, key);
    auto t_finish = chrono::high_resolution_clock::now();
    double time_bin = chrono::duration<double, micro>(t_finish - t_start).count();

    t_start = chrono::high_resolution_clock::now();
    int idx_int = interpolation_search(arr, n, key);
    t_finish = chrono::high_resolution_clock::now();
    double time_int = chrono::duration<double, micro>(t_finish - t_start).count();

    cout << "\nBinary Search index: " << idx_bin << endl;
    cout << "Binary Search time: " << time_bin << " microseconds\n";

    cout << "\nInterpolation Search index: " << idx_int << endl;
    cout << "Interpolation Search time: " << time_int << " microseconds\n";

    delete[] arr;
    return 0;
}