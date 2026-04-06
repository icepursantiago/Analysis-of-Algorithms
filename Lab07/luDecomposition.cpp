#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// LU Decomposition
void luDecomposition(vector<vector<double>>& A, 
                     vector<vector<double>>& L, 
                     vector<vector<double>>& U, int n) {
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));
    
    for (int i = 0; i < n; i++) {
        // Upper triangular matrix
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }
        
        // Lower triangular matrix
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1.0;
            } else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

// Forward substitution for Ly = b
void forwardSubstitution(const vector<vector<double>>& L, 
                        const vector<double>& b, 
                        vector<double>& y, int n) {
    y.assign(n, 0.0);
    
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

// Backward substitution for Ux = y
void backwardSubstitution(const vector<vector<double>>& U, 
                         const vector<double>& y, 
                         vector<double>& x, int n) {
    x.assign(n, 0.0);
    
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
}

// Solve system using LU decomposition
void solveLU(const vector<vector<double>>& A, 
             const vector<double>& b, 
             vector<double>& x, int n) {
    vector<vector<double>> ACopy = A;
    vector<vector<double>> L, U;
    
    // LU decomposition
    luDecomposition(ACopy, L, U, n);
    
    // Forward substitution
    vector<double> y;
    forwardSubstitution(L, b, y, n);
    
    // Backward substitution
    backwardSubstitution(U, y, x, n);
}

// Print matrix
void printMatrix(const vector<vector<double>>& A, const string& name) {
    cout << name << ":" << endl;
    for (const auto& row : A) {
        for (double val : row) {
            cout << fixed << setprecision(4) << setw(10) << val;
        }
        cout << endl;
    }
    cout << endl;
}

// Print vector
void printVector(const vector<double>& v, const string& name) {
    cout << name << ":" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "x[" << i << "] = " << fixed << setprecision(4) << v[i] << endl;
    }
    cout << endl;
}

int main() {
    int n = 3;
    
    // Example system: Ax = b
    vector<vector<double>> A = {
        {4, 3, 2},
        {6, 3, 4},
        {3, 2, 3}
    };
    
    vector<double> b = {1, 2, 3};
    
    cout << "System: Ax = b" << endl << endl;
    printMatrix(A, "Matrix A");
    printVector(b, "Vector b");
    
    // Compute LU decomposition
    vector<vector<double>> L, U;
    luDecomposition(A, L, U, n);
    
    printMatrix(L, "Lower Triangular Matrix L");
    printMatrix(U, "Upper Triangular Matrix U");
    
    // Solve system
    vector<double> x;
    solveLU(A, b, x, n);
    
    printVector(x, "Solution x");
    
    // Verify: Ax should equal b
    cout << "Verification (Ax = b):" << endl;
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        cout << "A[" << i << "] · x = " << fixed << setprecision(4) << sum 
             << " (expected: " << b[i] << ")" << endl;
    }
    
    return 0;
}