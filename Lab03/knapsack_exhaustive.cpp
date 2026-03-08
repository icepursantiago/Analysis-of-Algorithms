#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Item {
    int weight;
    int value;
};

struct Solution {
    int max_value;
    vector<bool> selection;
};

// Exhaustive search for 0/1 Knapsack
Solution knapsack_exhaustive(vector<Item>& items, int capacity) {
    int n = items.size();
    int total_combinations = 1 << n;  // 2^n combinations
    Solution best;
    best.max_value = 0;
    best.selection.resize(n, false);
    
    for (int mask = 0; mask < total_combinations; mask++) {
        int current_weight = 0;
        int current_value = 0;
        vector<bool> current_selection(n, false);
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                current_weight += items[i].weight;
                current_value += items[i].value;
                current_selection[i] = true;
            }
        }
        
        if (current_weight <= capacity && current_value > best.max_value) {
            best.max_value = current_value;
            best.selection = current_selection;
        }
    }
    
    return best;
}

// Generate random instance
vector<Item> generate_random_instance(int n, int max_weight, int max_value) {
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        items[i].weight = (rand() % max_weight) + 1;
        items[i].value = (rand() % max_value) + 1;
    }
    return items;
}

void empirical_analysis() {
    srand(time(0));
    ofstream file("knapsack_analysis.csv");
    file << "n,Combinations,Time_ms,Max_Value\n";
    
    cout << "\n=== 0/1 KNAPSACK EXHAUSTIVE SEARCH ===\n";
    cout << "Finding maximum n solvable in 10 minutes...\n\n";
    cout << "n\tCombinations\tTime(ms)\tMax Value\n";
    cout << "-----------------------------------------------\n";
    
    int n = 4;
    double time_limit_ms = 600000.0; // 10 minutes
    
    while (true) {
        long long combinations = 1LL << n;
        
        // Generate random instance
        int capacity = n * 10;
        vector<Item> items = generate_random_instance(n, 20, 50);
        
        auto t_start = chrono::high_resolution_clock::now();
        Solution solution = knapsack_exhaustive(items, capacity);
        auto t_finish = chrono::high_resolution_clock::now();
        
        double elapsed = chrono::duration<double, milli>(t_finish - t_start).count();
        
        cout << n << "\t" << combinations << "\t\t" 
             << elapsed << "\t" << solution.max_value << endl;
        
        file << n << "," << combinations << "," 
             << elapsed << "," << solution.max_value << "\n";
        
        if (elapsed > time_limit_ms) {
            cout << "\n✓ Maximum n found: " << (n-1) << endl;
            cout << "✓ Time exceeded 10 minutes at n=" << n << endl;
            break;
        }
        
        if (n > 30) {
            cout << "\n✓ Reached safety limit (n=30)\n";
            break;
        }
        
        n++;
    }
    
    file.close();
    cout << "\n✓ Data saved to 'knapsack_analysis.csv'\n";
}

int main() {
    int choice;
    cout << "=== 0/1 KNAPSACK PROBLEM ===\n";
    cout << "1. Demo with small instance\n";
    cout << "2. Empirical Analysis\n";
    cout << "Choose option: ";
    cin >> choice;
    
    if (choice == 1) {
        srand(time(0));
        int n = 8;
        int capacity = 50;
        
        vector<Item> items = generate_random_instance(n, 20, 50);
        
        cout << "\nGenerated instance (n=" << n << ", capacity=" << capacity << "):\n";
        for (int i = 0; i < n; i++) {
            cout << "Item " << i+1 << ": weight=" << items[i].weight 
                 << ", value=" << items[i].value << endl;
        }
        
        Solution solution = knapsack_exhaustive(items, capacity);
        
        cout << "\nOptimal solution:\n";
        cout << "Maximum value: " << solution.max_value << endl;
        cout << "Selected items: ";
        for (int i = 0; i < n; i++) {
            if (solution.selection[i]) {
                cout << (i+1) << " ";
            }
        }
        cout << endl;
        
    } else if (choice == 2) {
        empirical_analysis();
    }
    
    return 0;
}
