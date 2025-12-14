#include <iostream>
using namespace std;

int sensors = 5;

// Adjacency matrix: connectivity between forest sensors
int forestGraph[10][10] = {
    {0,1,1,0,0},
    {1,0,0,1,1},
    {1,0,0,0,1},
    {0,1,0,0,0},
    {0,1,1,0,0}
};

int visited[10];

// DFS to explore deep forest sensor connectivity
void dfs(int graph[10][10], int sensors, int source) {
    visited[source] = 1;

    for (int i = 0; i < sensors; i++) {
        if (graph[source][i] == 1 && visited[i] == 0) {
            cout << "Sensor " << i << "\t";
            dfs(graph, sensors, i);
        }
    }
}

int main() {
    int source;

    for (int i = 0; i < sensors; i++)
        visited[i] = 0;

    cout << "Enter source sensor node (fire detected location): ";
    cin >> source;

    cout << "\nDFS Traversal (Deep Fire Spread Analysis):\n";
    cout << "Sensor " << source << "\t";
    dfs(forestGraph, sensors, source);

    return 0;
}
