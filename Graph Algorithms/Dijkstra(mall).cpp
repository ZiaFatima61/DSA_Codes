#include <iostream>
using namespace std;

#define MAXN 100
#define INF 999

int main() {
    int n;
    cout << "Enter number of locations (stores / lifts / escalators): ";
    cin >> n;

    int cost[MAXN][MAXN];

    cout << "Enter cost matrix (Enter 999 if no direct path)\n";
    cout << "Cost includes distance + waiting time + convenience\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    int source;
    cout << "Enter source location: ";
    cin >> source;

    int dist[MAXN], parent[MAXN], visited[MAXN];

    // Initialization
    for (int i = 0; i < n; i++) {
        dist[i] = cost[source][i];
        parent[i] = source;
        visited[i] = 0;
    }

    dist[source] = 0;
    visited[source] = 1;
    parent[source] = -1;

    // Dijkstra’s Algorithm
    for (int iter = 0; iter < n - 1; iter++) {
        int u = -1;
        int minDist = INF;

        // Find unvisited node with minimum distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        // Update distances
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] != INF) {
                if (dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Output result
    cout << "\nLocation   Minimum Cost   Previous Location\n";
    for (int i = 0; i < n; i++) {
        cout << i << "            " << dist[i] << "               " << parent[i] << "\n";
    }

    return 0;
}
