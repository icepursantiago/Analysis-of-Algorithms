#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<int> w(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) {
        cout << "Enter weight and value for item " << i << ": ";
        cin >> w[i] >> v[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int c = 0; c <= W; c++) {
            dp[i][c] = dp[i - 1][c];
            if (w[i] <= c) {
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i]] + v[i]);
            }
        }
    }

    cout << "Maximum value: " << dp[n][W] << endl;

    // Reconstruct chosen items
    int c = W;
    vector<int> chosen;
    for (int i = n; i >= 1; i--) {
        if (dp[i][c] != dp[i - 1][c]) {
            chosen.push_back(i);
            c -= w[i];
        }
    }
    reverse(chosen.begin(), chosen.end());

    cout << "Chosen item indices: ";
    for (int idx : chosen) cout << idx << " ";
    cout << endl;

    return 0;
}
