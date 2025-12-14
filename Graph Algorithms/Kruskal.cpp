#include <iostream>
using namespace std;

// Structure representing a wiring connection in the mall
struct Connection {
    int location1;   // Store / Security room / Router
    int location2;
    int cost;        // Wiring / network cost
};

// Bubble Sort to sort connections by cost
void bubbleSort(Connection edges[], int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (edges[j].cost > edges[j + 1].cost) {
                Connection temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Union operation (simple union-find)
void Union(int parent[], int n, int u, int v) {
    int temp = parent[u];
    for (int i = 0; i < n; i++) {
        if (parent[i] == temp)
            parent[i] = parent[v];
    }
}

// Find operation (check if two locations are already connected)
bool Find(int parent[], int u, int v) {
    return parent[u] == parent[v];
}

int main() {
    int n, m;
    cout << "Enter number of mall locations and connections: ";
    cin >> n >> m;

    Connection edges[100];

    cout << "Enter connections as: Location1 Location2 Cost\n";
    cout << "(Example: 0 1 500)\n";

    for (int i = 0; i < m; i++) {
        cin >> edges[i].location1 >> edges[i].location2 >> edges[i].cost;
    }

    int parent[100];
    for (int i = 0; i < n; i++)
        parent[i] = i;

    // Step 1: Sort connections by cost
    bubbleSort(edges, m);

    int totalCost = 0;

    cout << "\nConnections selected for Minimum Cost Network:\n";

    // Step 2: Select edges using Kruskal’s Algorithm
    for (int i = 0; i < m; i++) {
        int u = edges[i].location1;
        int v = edges[i].location2;
        int w = edges[i].cost;

        if (!Find(parent, u, v)) {
            cout << "Location " << u << " -- Location " << v
                 << " : Cost = " << w << endl;
            totalCost += w;
            Union(parent, n, u, v);
        }
    }

    cout << "\nTotal Minimum Wiring Cost = " << totalCost << endl;

    return 0;
}
