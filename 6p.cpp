#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 6;
string places[N] = {"College", "Library", "Cafeteria", "Hostel", "Playground", "Auditorium"};

int adjMatrix[N][N] = {0};

vector<int> adjList[N];

void dfs(int node, vector<bool>& visited) {
    visited[node] = true;
    cout << places[node] << " ";

    for (int neighbor : adjList[node]) {
        if (!visited[neighbor])
            dfs(neighbor, visited);
    }
}

void bfs(int start) {
    vector<bool> visited(N, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << places[node] << " ";

        for (int i = 0; i < N; i++) {
            if (adjMatrix[node][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {

    auto addEdge = [](int u, int v) {
    
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

    
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    };

    addEdge(0, 1); 
    addEdge(0, 2); 
    addEdge(1, 3);
    addEdge(2, 4); 
    addEdge(4, 5); 

    cout << "DFS (Adjacency List): ";
    vector<bool> visited(N, false);
    dfs(0, visited); 
    cout << endl;

    cout << "BFS (Adjacency Matrix): ";
    bfs(0); 
    cout << endl;

    return 0;
}
