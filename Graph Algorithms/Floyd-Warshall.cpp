#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 9999  // Represent no direct connection

int main() {
    int numSpots;
    cout << "Enter the number of tourist spots: ";
    cin >> numSpots;
    cin.ignore(); // Clear input buffer

    vector<string> spots(numSpots);
    cout << "Enter the names of the tourist spots:\n";
    for (int i = 0; i < numSpots; i++) {
        getline(cin, spots[i]);
    }

    // Initialize distance matrix
    vector<vector<int>> dist(numSpots, vector<int>(numSpots, INF));

    // Input cost between spots
    cout << "\nEnter the travel cost between spots (use 0 if same spot, -1 if no direct path):\n";
    for (int i = 0; i < numSpots; i++) {
        for (int j = 0; j < numSpots; j++) {
            if (i == j) {
                dist[i][j] = 0;
                continue;
            }
            cout << "Cost from " << spots[i] << " to " << spots[j] << ": ";
            int cost;
            cin >> cost;
            if (cost == -1) dist[i][j] = INF;
            else dist[i][j] = cost;
        }
    }

    // Floyd–Warshall algorithm
    for (int k = 0; k < numSpots; k++) {
        for (int i = 0; i < numSpots; i++) {
            for (int j = 0; j < numSpots; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Display shortest travel costs
    cout << "\nOptimized travel cost between all tourist spots:\n\n";
    cout << "\t";
    for (int i = 0; i < numSpots; i++) cout << spots[i] << "\t";
    cout << "\n";

    for (int i = 0; i < numSpots; i++) {
        cout << spots[i] << "\t";
        for (int j = 0; j < numSpots; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << "\n";
    }

    return 0;
}
