#include <iostream>
#include <chrono>
#define MAX 100
using namespace std;

int Fibonacci(int n) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }
    return Fibonacci(n - 2) + Fibonacci(n - 1);
}

int fib(int n, int memo[]) {
    if (n == 0) { return 0; }
    if (memo[n] != 0) {
        return memo[n];
    }
    if (n == 1) {
        memo[n] = 1;
        return 1;
    }
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

int print_fibonacci(int n) {
    n++;
    for (int i = 0; i < n; i++) {
        cout << Fibonacci(i) << " ";
    }
    cout << endl;
    return 0;
}

int main() {
    int n;
    int memo[MAX] = { 0 };

    cout << "Enter the index number of the fibonacci number: ";
    cin >> n;

    if (n < 0 || n >= MAX) {
        cerr << "n must be in range [0, " << (MAX - 1) << "]\n";
        return 1;
    }

    // Time plain recursion
    const auto t1 = chrono::high_resolution_clock::now();
    const int r1 = Fibonacci(n);
    const auto t2 = chrono::high_resolution_clock::now();

    // Time memoized DP
    const int r2 = fib(n, memo);
    const auto t3 = chrono::high_resolution_clock::now();

    const auto rec_us = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    const auto dp_us  = chrono::duration_cast<chrono::microseconds>(t3 - t2).count();

    cout << r1 << endl;
    cout << "Dynamic Programming:" << endl;
    cout << r2 << endl;

    cout << "Time (plain recursion): " << rec_us << " us" << endl;
    cout << "Time (memorized DP):     " << dp_us  << " us" << endl;

    cout << "Fibonacci sequence:" << endl;
    print_fibonacci(n);

    return 0;
}
