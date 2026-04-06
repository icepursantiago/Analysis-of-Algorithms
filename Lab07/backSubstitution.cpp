#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Back substitution function
void backSubstitution(const vector<vector<double>>& A, 
                      vector<double>& x, int n) {
    x.resize(n);
    
    for (int j = n - 1; j >= 0; j--) {
        double t = 0.0;
        for (int k = j + 1; k < n; k++) {
            t = t + A[j][k] * x[k];
        }
        if (abs(A[j][j]) < 1e-10) {
            cerr << "Matrix is singular!" << endl;
            return;
        }
        x[j] = (A[j][n] - t) / A[j][j];
    }
}

// Print solution
void printSolution(const vector<double>& x) {
    cout << "Solution:" << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << "x[" << (i+1) << "] = " 
             << fixed << setprecision(4) << x[i] << endl;
    }
}

int main() {
    // Upper triangular matrix after forward elimination
    int n = 3;
    vector<vector<double>> A = {
        {2, 1, -1, 8},
        {0, 1, 1, 5},
        {0, 0, 3, 3}
    };
    
    vector<double> x;
    backSubstitution(A, x, n);
    printSolution(x);
    
    return 0;
}