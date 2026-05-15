#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
        adj[v].push_back(u); // Undirected graph
    }

    // Sequential BFS
    void sequentialBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nSequential BFS: ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Parallel BFS using OpenMP
    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS: ";

        while (!q.empty()) {
            int node;

            #pragma omp critical
            {
                if (!q.empty()) {
                    node = q.front();
                    q.pop();
                    cout << node << " ";
                }
            }

            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {
                int neighbor = adj[node][i];

                if (!visited[neighbor]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    // Sequential DFS Utility
    void sequentialDFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                sequentialDFSUtil(neighbor, visited);
            }
        }
    }

    // Sequential DFS
    void sequentialDFS(int start) {
        vector<bool> visited(V, false);

        cout << "\nSequential DFS: ";
        sequentialDFSUtil(start, visited);

        cout << endl;
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

    // Parallel DFS
    void parallelDFS(int start) {
        vector<bool> visited(V, false);

        cout << "\nParallel DFS: ";

        #pragma omp parallel
        {
            #pragma omp single
            {
                parallelDFSUtil(start, visited);
            }
        }

        cout << endl;
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

    g.sequentialBFS(start);

    g.parallelBFS(start);

    g.sequentialDFS(start);

    g.parallelDFS(start);

    return 0;
}

/*Enter number of vertices: 6
Enter number of edges: 7

Enter edges (u v):
0 1
0 2
1 3
1 4
2 4
3 5
4 5

Enter starting vertex: 0
*/