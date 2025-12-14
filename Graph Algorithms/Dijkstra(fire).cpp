#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX_LOCATIONS 100
#define INF 999

// Function to print path from fire location to water source
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
    cout << "Enter the number of points in the forest (sensors, towers, water sources, fire-prone zones):\n";
    cin >> numLocations;

    vector<string> locationNames(numLocations);
    cout << "Enter the names of the locations:\n";
    cin.ignore(); // clear newline
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

    int fireLocation;
    cout << "Enter the fire location index (where fire is detected):\n";
    cin >> fireLocation;

    int shortestDistance[MAX_LOCATIONS], previous[MAX_LOCATIONS], visited[MAX_LOCATIONS];

    // Initialize distances and visited
    for (int i = 0; i < numLocations; i++) {
        shortestDistance[i] = distanceMatrix[fireLocation][i];
        previous[i] = fireLocation;
        visited[i] = 0;
    }
    visited[fireLocation] = 1;
    previous[fireLocation] = fireLocation;

    // Dijkstra algorithm
    for (int iter = 0; iter < numLocations - 1; iter++) {
        int u = -1;
        int minDistance = INF + 1;

        // Find unvisited location with smallest distance
        for (int i = 0; i < numLocations; i++) {
            if (!visited[i] && shortestDistance[i] < minDistance) {
                minDistance = shortestDistance[i];
                u = i;
            }
        }

        if (u == -1) break; // no reachable unvisited location
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

    // Ask user which points are water sources
    int numWaterSources;
    cout << "Enter the number of water sources:\n";
    cin >> numWaterSources;

    vector<int> waterSources(numWaterSources);
    cout << "Enter the indices of water sources:\n";
    for (int i = 0; i < numWaterSources; i++) {
        cin >> waterSources[i];
    }

    // Find nearest water source
    int nearestWater = waterSources[0];
    for (int ws : waterSources) {
        if (shortestDistance[ws] < shortestDistance[nearestWater]) {
            nearestWater = ws;
        }
    }

    cout << "\nShortest path from fire location (" << locationNames[fireLocation] << ") to nearest water source ("
         << locationNames[nearestWater] << "):\n";
    cout << "Distance: " << shortestDistance[nearestWater] << "\nPath: ";
    printPath(nearestWater, previous, locationNames);
    cout << endl;

    return 0;
}
