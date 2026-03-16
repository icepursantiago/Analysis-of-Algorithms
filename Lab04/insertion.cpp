#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertion_sort(char arr[], int n){
    for(int i = 1; i < n; ++i){
        char key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void print_array(char arr[], int n){
    for(int i = 0; i < n; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void generate_random_chars(char arr[], int n){
    for(int i = 0; i < n; ++i){
        arr[i] = char('A' + (rand() % 26));
    }
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

    char *arr = new char[n];
    generate_random_chars(arr, n);

    if(n <= 50){
        cout << "\nUnsorted array:\n";
        print_array(arr, n);
    }

    auto t_start = chrono::high_resolution_clock::now();
    insertion_sort(arr, n);
    auto t_finish = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration<double, milli>(t_finish - t_start).count();

    if(n <= 50){
        cout << "\nSorted array:\n";
        print_array(arr, n);
    }

    cout << "\nInsertion Sort time: " << elapsed << " ms" << endl;

    delete[] arr;
    return 0;
}
