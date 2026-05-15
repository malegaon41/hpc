#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph {

    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected Graph
    }

    // Parallel DFS Utility
    void parallelDFSUtil(int node, vector<bool>& visited) {

        #pragma omp critical
        {
            visited[node] = true;
            cout << node << " ";
        }

        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!visited[neighbor]) {

                #pragma omp task
                parallelDFSUtil(neighbor, visited);
            }
        }
    }

    // Parallel DFS Function
    void parallelDFS(int start) {

        vector<bool> visited(V, false);

        cout << "Parallel DFS Traversal: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                parallelDFSUtil(start, visited);
            }
        }
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < E; i++) {

        int u, v;

        cin >> u >> v;

        g.addEdge(u, v);
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    g.parallelDFS(start);

    return 0;
}