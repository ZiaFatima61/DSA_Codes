#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define INF 9999  // Represents no direct route

int main() {
    int numNodes;
    cout << "Enter the number of nodes in the water network: ";
    cin >> numNodes;
    cin.ignore(); // Clear input buffer

    vector<string> nodes(numNodes);
    cout << "Enter the names of nodes (reservoirs/pumps/etc.):\n";
    for (int i = 0; i < numNodes; i++) {
        getline(cin, nodes[i]);
    }

    // Initialize adjacency matrix with INF
    vector<vector<int>> flowCost(numNodes, vector<int>(numNodes, INF));

    cout << "\nEnter flow cost between nodes (-1 if no direct route, 0 for same node):\n";
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (i == j) {
                flowCost[i][j] = 0;
                continue;
            }
            cout << "Cost from " << nodes[i] << " to " << nodes[j] << ": ";
            int cost;
            cin >> cost;
            if (cost == -1) flowCost[i][j] = INF;
            else flowCost[i][j] = cost;
        }
    }

    // Floyd–Warshall algorithm
    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (flowCost[i][k] + flowCost[k][j] < flowCost[i][j]) {
                    flowCost[i][j] = flowCost[i][k] + flowCost[k][j];
                }
            }
        }
    }

    // Display shortest flow paths between all pairs
    cout << "\nOptimized flow cost between all nodes:\n\n";
    cout << "\t";
    for (int i = 0; i < numNodes; i++) cout << nodes[i] << "\t";
    cout << "\n";

    for (int i = 0; i < numNodes; i++) {
        cout << nodes[i] << "\t";
        for (int j = 0; j < numNodes; j++) {
            if (flowCost[i][j] == INF)
                cout << "INF\t";
            else
                cout << flowCost[i][j] << "\t";
        }
        cout << "\n";
    }

    return 0;
}
