#include <bits/stdc++.h>
using namespace std;
#define int long long
const long long INF = 1e18;

bool bellman(vector<vector<int>>& graph, vector<bool>& visited, int src, int n) {
    vector<int> dist(n + 1, INF);
    dist[src] = 0;
    vector<int> parent(n + 1, -1);
    
    // Relax all edges n-1 times
    for (int i = 0; i < n ; i++) {
        bool updated = false;
        for (auto& edge : graph) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                visited[v] = true;
                updated = true;
            }
        }
        if (!updated) break;
    }
    
    // Check for negative-weight cycles
    for (auto& edge : graph) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "YES\n";
            
            // Find a vertex in the cycle
            int cycle_vertex = v;
            for (int i = 0; i < n; i++) {
                cycle_vertex = parent[cycle_vertex];
            }
            
            // Reconstruct the cycle
            vector<int> cycle;
            int current = cycle_vertex;
            do {
                cycle.push_back(current);
                current = parent[current];
            } while (current != cycle_vertex);
            cycle.push_back(cycle_vertex);
            
            // Print the cycle
            reverse(cycle.begin(), cycle.end());
            for (int node : cycle) {
                cout << node << " ";
            }
            cout << "\n";
            return true;
        }
    }
    
    return false;
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.push_back({a, b, c});
    }
    
    vector<bool> visited(n + 1, false);
    bool has_negative_cycle = false;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            has_negative_cycle = bellman(graph, visited, i, n);
            if (has_negative_cycle) {
                break;
            }
        }
    }
    
    if (!has_negative_cycle) {
        cout << "NO\n";
    }
    
    return 0;
}