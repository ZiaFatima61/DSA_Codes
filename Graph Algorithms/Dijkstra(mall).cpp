#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX_LOCATIONS 100
#define INF 999

// Function to print the path using store names
void printPath(int location, int previous[], vector<string>& names) {
    if (previous[location] == location) {
        cout << names[location];
        return;
    }
    printPath(previous[location], previous, names);
    cout << " -> " << names[location];
}

int main() {
    int numLocations;
    cout << "Enter the number of locations in the mall:\n";
    cin >> numLocations;

    vector<string> locationNames(numLocations);
    cout << "Enter the names of the locations (e.g., Entrance, Electronics, Food Court):\n";
    cin.ignore(); // To ignore leftover newline
    for (int i = 0; i < numLocations; i++) {
        getline(cin, locationNames[i]);
    }

    int distanceMatrix[MAX_LOCATIONS][MAX_LOCATIONS];
    cout << "Enter the distance matrix (Enter 999 if locations are not directly connected):\n";
    for (int i = 0; i < numLocations; i++) {
        for (int j = 0; j < numLocations; j++) {
            cin >> distanceMatrix[i][j];
        }
    }

    int startLocation;
    cout << "Enter the starting location index (0 to " << numLocations-1 << ", e.g., entrance):\n";
    cin >> startLocation;

    int shortestDistance[MAX_LOCATIONS], previous[MAX_LOCATIONS], visited[MAX_LOCATIONS];

    // Initialize distances and visited
    for (int i = 0; i < numLocations; i++) {
        shortestDistance[i] = distanceMatrix[startLocation][i];
        previous[i] = startLocation;
        visited[i] = 0;
    }
    visited[startLocation] = 1;
    previous[startLocation] = startLocation;

    // Dijkstra algorithm
    for (int iter = 0; iter < numLocations - 1; iter++) {
        int u = -1;
        int minDistance = INF + 1;

        // Find the unvisited location with the smallest distance
        for (int i = 0; i < numLocations; i++) {
            if (!visited[i] && shortestDistance[i] < minDistance) {
                minDistance = shortestDistance[i];
                u = i;
            }
        }

        if (u == -1) break; // No reachable unvisited location
        visited[u] = 1;

        // Update distances for neighbors
        for (int v = 0; v < numLocations; v++) {
            if (!visited[v] && distanceMatrix[u][v] != INF) {
                if (shortestDistance[u] + distanceMatrix[u][v] < shortestDistance[v]) {
                    shortestDistance[v] = shortestDistance[u] + distanceMatrix[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    // Display shortest paths from entrance to each location
    cout << "\nLocation          Distance from Entrance   Path\n";
    for (int i = 0; i < numLocations; i++) {
        cout << locationNames[i] << "          " << shortestDistance[i] << "                    ";
        printPath(i, previous, locationNames);
        cout << "\n";
    }

    return 0;
}

