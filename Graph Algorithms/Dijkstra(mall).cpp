#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX 100
#define INF 999

// Function to print the path using location names
void printPath(int node, int parent[], vector<string>& locationNames)
{
    if (parent[node] == node)
    {
        cout << locationNames[node];
        return;
    }
    printPath(parent[node], parent, locationNames);
    cout << " -> " << locationNames[node];
}

int main()
{
    int n;
    cout << "Enter number of locations in the shopping mall: ";
    cin >> n;

    vector<string> locationNames(n);
    cout << "Enter location names (Entrance, Elevator, Store, Food Court, etc.):\n";
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        getline(cin, locationNames[i]);
    }

    int cost[MAX][MAX];
    cout << "Enter distance matrix (999 for no direct path):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    int source;
    cout << "Enter source location index (Entrance): ";
    cin >> source;

    int dist[MAX], parent[MAX], visited[MAX];

    // Initialization
    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[source][i];
        parent[i] = source;
        visited[i] = 0;
    }

    dist[source] = 0;
    parent[source] = source;
    visited[source] = 1;

    // Dijkstra’s Algorithm
    for (int count = 0; count < n - 1; count++)
    {
        int u = -1;
        int minDist = INF;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && cost[u][v] != INF)
            {
                if (dist[u] + cost[u][v] < dist[v])
                {
                    dist[v] = dist[u] + cost[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Output
    cout << "\nShortest paths from Entrance:\n";
    cout << "Location\tDistance\tPath\n";

    for (int i = 0; i < n; i++)
    {
        cout << locationNames[i] << "\t\t" << dist[i] << "\t\t";
        printPath(i, parent, locationNames);
        cout << endl;
    }

    return 0;
}
