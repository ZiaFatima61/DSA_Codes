#include <iostream>
using namespace std;

#define MAXN 100
#define INF 999

int main() {
    int n;
    cout << "Enter number of sensor nodes in the forest:\n";
    cin >> n;

    int cost[MAXN][MAXN];

    cout << "Enter wiring/communication cost matrix (Enter 999 if no direct link):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    int source;
    cout << "Enter starting sensor node (base station):\n";
    cin >> source;

    int minCost[MAXN], parent[MAXN], visited[MAXN];

    // Initialization
    for (int i = 0; i < n; i++) {
        minCost[i] = cost[source][i];
        parent[i] = source;
        visited[i] = 0;
    }

    minCost[source] = 0;
    parent[source] = -1;   // Root sensor
    visited[source] = 1;

    int totalCost = 0;

    // Prim’s Algorithm
    for (int iter = 0; iter < n - 1; iter++) {
        int u = -1;
        int min = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && minCost[i] < min) {
                min = minCost[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;
        totalCost += minCost[u];

        for (int v = 0; v < n; v++) {
            if (!visited[v] && cost[u][v] != INF && cost[u][v] < minCost[v]) {
                minCost[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }

    // Output
    cout << "\nMinimum Wiring Connections Between Sensors:\n";
    cout << "Sensor A  -  Sensor B   :  Cost\n";
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            cout << parent[v] << "  -  " << v
                 << "   :   " << minCost[v] << "\n";
        }
    }

    cout << "Total minimum wiring cost = " << totalCost << "\n";

    return 0;
}
