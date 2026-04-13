#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

// Stable ComparisonCountingSort by breaking ties with indices.
// For each i, count how many elements are smaller than A[i],
// or equal but appear earlier (j < i). That count is the final position.
static void comparisonCountingSort(vector<int> &A) {
    int n = (int)A.size();
    vector<int> C(n, 0);
    vector<int> B(n, 0);

    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (A[j] < A[i] || (A[j] == A[i] && j < i)) {
                cnt++;
            }
        }
        C[i] = cnt;
    }

    for (int i = 0; i < n; i++) {
        B[C[i]] = A[i];
    }

    A = B;
}

static void printArray(const vector<int> &A, const string &label) {
    cout << label << ": ";
    for (int x : A) cout << x << " ";
    cout << "\n";
}

int main() {
    cout << "=== Problem 2: ComparisonCountingSort ===\n\n";

    // Test 1: fixed example with duplicates
    vector<int> A1 = {5, 1, 4, 1, 3, 5, 2, 2};
    printArray(A1, "Original");
    comparisonCountingSort(A1);
    printArray(A1, "Sorted  ");
    cout << "\n";

    // Test 2: random example
    mt19937 rng(2026);
    uniform_int_distribution<int> dist(-5, 9);

    vector<int> A2(15);
    for (int i = 0; i < (int)A2.size(); i++) A2[i] = dist(rng);

    printArray(A2, "Original");
    comparisonCountingSort(A2);
    printArray(A2, "Sorted  ");

    return 0;
}