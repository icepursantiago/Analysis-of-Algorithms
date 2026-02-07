// Lab01: Fibonacci Sequence
// Author: Aispur Santiago
// Date: 2026-02-08

#include <iostream>
using namespace std;

int fibo_recursive(int n){
    if (n <= 1){
        return n;
    }
    else if (n == 2){
        return 1;
    }
    else{
        return fibo_recursive(n - 1) + fibo_recursive(n - 2);
    }
}

int fibo_iterative(int n){
    if (n <= 1){
        return n;
    }
    int a = 0;
    int b = 1;
    int c;
    for (int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void print_fibo_sequence(int n){
    cout << " Recursive Fibonacci sequence up to " << n << " terms: ";
    for (int i = 1; i <= n; i++){
        cout << fibo_recursive(i) << " ";
    }  
    cout << endl;
}

void print_fibo_sequence_i(int n){
    cout << " Iterative Fibonacci sequence up to " << n << " terms: ";
    for (int i = 1; i <= n; i++){
        cout << fibo_iterative(i) << " ";
    }  
    cout << endl;
}

int main(){
    int n = 20;
    print_fibo_sequence(n);
    print_fibo_sequence_i(n);
    return 0;
}
