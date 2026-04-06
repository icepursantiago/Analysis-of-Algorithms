#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Forward elimination function
void forwardElimination(vector<vector<double>>& A, vector<double>& b, int n) {
    // Augment the matrix with b vector
    for (int i = 0; i < n; i++) {
        A[i].push_back(b[i]);
    }
    
    // Forward elimination
    for (int i = 0; i < n - 1; i++) {
        // Find pivot
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        
        // Swap rows
        swap(A[i], A[maxRow]);
        
        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            if (abs(A[i][i]) < 1e-10) {
                cerr << "Matrix is singular!" << endl;
                return;
            }
            double factor = A[k][i] / A[i][i];
            for (int j = i; j <= n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
}

// Print matrix
void printMatrix(const vector<vector<double>>& A) {
    for (const auto& row : A) {
        for (double val : row) {
            cout << fixed << setprecision(4) << setw(10) << val;
        }
        cout << endl;
    }
}

int main() {
    int n = 3;
    vector<vector<double>> A = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };
    vector<double> b = {8, -11, -3};
    
    cout << "Original Augmented Matrix:" << endl;
    printMatrix(A);
    
    forwardElimination(A, b, n);
    
    cout << "\nAfter Forward Elimination (Upper Triangular):" << endl;
    printMatrix(A);
    
    return 0;
}
