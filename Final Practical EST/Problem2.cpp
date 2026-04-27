#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src) {
    vector<int> dist(V, 1e8); 
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
            return {-1};
        }
    }

    return dist;
}

int main() {
    int V = 5;
    vector<vector<int>> edges = {
        {1, 3, 2},
        {4, 3, -1},
        {2, 4, 1},
        {1, 2, 1},
        {0, 1, 5}};

    int src = 0;

    vector<int> result = bellmanFord(V, edges, src);

    for (int x : result)
        cout << x << " ";
    return 0;
}