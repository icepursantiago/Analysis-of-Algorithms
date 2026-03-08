#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adj_list;
    
public:
    Graph(int v) {
        vertices = v;
        adj_list.resize(v);
    }
    
    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
    }
    
    void DFS(int start) {
        vector<bool> visited(vertices, false);
        stack<int> s;
        
        s.push(start);
        cout << "DFS traversal starting from node " << start << ": ";
        
        while (!s.empty()) {
            int node = s.top();
            s.pop();
            
            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
                
                // Push adjacent nodes (in reverse order for correct traversal)
                for (int i = adj_list[node].size() - 1; i >= 0; i--) {
                    if (!visited[adj_list[node][i]]) {
                        s.push(adj_list[node][i]);
                    }
                }
            }
        }
        cout << endl;
    }
    
    void DFS_recursive(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        
        for (int neighbor : adj_list[node]) {
            if (!visited[neighbor]) {
                DFS_recursive(neighbor, visited);
            }
        }
    }
    
    void DFS_recursive_wrapper(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS recursive traversal starting from node " << start << ": ";
        DFS_recursive(start, visited);
        cout << endl;
    }
    
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "BFS traversal starting from node " << start << ": ";
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            
            for (int neighbor : adj_list[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    
    void print_graph() {
        cout << "\nGraph structure (Adjacency List):\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Node " << i << ": ";
            for (int neighbor : adj_list[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== GRAPH TRAVERSAL ALGORITHMS ===\n\n";
    
    // Create sample graph
    Graph g(7);
    
    // Add edges (directed graph)
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 5);
    g.add_edge(2, 6);
    g.add_edge(3, 4);
    g.add_edge(5, 6);
    
    g.print_graph();
    
    cout << "\n--- Depth First Search (DFS) ---\n";
    g.DFS(0);
    g.DFS_recursive_wrapper(0);
    
    cout << "\n--- Breadth First Search (BFS) ---\n";
    g.BFS(0);
    
    cout << "\n=== COMPLEXITY ANALYSIS ===\n";
    cout << "Data structure: Adjacency List\n";
    cout << "DFS Time: O(V + E)\n";
    cout << "DFS Space: O(V) for stack\n";
    cout << "BFS Time: O(V + E)\n";
    cout << "BFS Space: O(V) for queue\n";
    
    return 0;
}