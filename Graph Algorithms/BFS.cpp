#include <iostream>
using namespace std;

// BFS to traverse forest sensor network
void bfs(int graph[10][10], int sensors, int source) {
    int queue[20];
    int front = 0, rear = 0, u, i;
    int visited[10];

    // Initialize visited sensors
    for (i = 0; i < sensors; i++)
        visited[i] = 0;

    queue[rear] = source;
    visited[source] = 1;

    cout << "\nBFS Traversal (Sensor-to-Sensor Connectivity):\n";

    while (front <= rear) {
        u = queue[front];
        cout << "Sensor " << u << "\t";
        front++;

        for (i = 0; i < sensors; i++) {
            // Edge represents connectivity between sensors
            if (graph[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
}

int main() {
    int sensors = 5;

    // Adjacency matrix: 1 means sensors are connected
    int forestGraph[10][10] = {
        {0,1,1,0,0},
        {1,0,0,1,1},
        {1,0,0,0,1},
        {0,1,0,0,0},
        {0,1,1,0,0}
    };

    int source;
    cout << "Enter source sensor node (fire detected location): ";
    cin >> source;

    bfs(forestGraph, sensors, source);

    return 0;
}
