#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Disjoint Set (Union-Find) functions
int findParent(vector<int>& parent, int node) {
    if (parent[node] == node) return node;
    return parent[node] = findParent(parent, parent[node]); // Path compression
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    int pu = findParent(parent, u);
    int pv = findParent(parent, v);
    if (pu == pv) return;

    if (rank[pu] < rank[pv]) parent[pu] = pv;
    else if (rank[pu] > rank[pv]) parent[pv] = pu;
    else {
        parent[pv] = pu;
        rank[pu]++;
    }
}

int main() {
    int numNodes;
    cout << "Enter the number of nodes in the water network: ";
    cin >> numNodes;
    cin.ignore();

    vector<string> nodes(numNodes);
    unordered_map<string, int> nodeIndex;

    cout << "Enter the names of nodes (reservoirs/pumps/tanks):\n";
    for (int i = 0; i < numNodes; i++) {
        getline(cin, nodes[i]);
        nodeIndex[nodes[i]] = i;
    }

    vector<int> parent(numNodes), rank(numNodes, 0);
    for (int i = 0; i < numNodes; i++) parent[i] = i;

    int numConnections;
    cout << "Enter the number of direct connections (pipes): ";
    cin >> numConnections;
    cin.ignore();

    cout << "Enter each connection as two node names separated by comma (e.g., Reservoir1,PumpStation1):\n";
    for (int i = 0; i < numConnections; i++) {
        string input, nodeA, nodeB;
        getline(cin, input);
        size_t comma = input.find(',');
        nodeA = input.substr(0, comma);
        nodeB = input.substr(comma + 1);
        if (nodeIndex.find(nodeA) != nodeIndex.end() && nodeIndex.find(nodeB) != nodeIndex.end()) {
            unionSets(parent, rank, nodeIndex[nodeA], nodeIndex[nodeB]);
        } else {
            cout << "Invalid node names: " << nodeA << ", " << nodeB << endl;
        }
    }

    // Find connected regions
    vector<vector<string>> regions(numNodes);
    for (int i = 0; i < numNodes; i++) {
        int p = findParent(parent, i);
        regions[p].push_back(nodes[i]);
    }

    cout << "\nWater supply regions:\n";
    int regionCount = 0;
    for (int i = 0; i < numNodes; i++) {
        if (!regions[i].empty()) {
            regionCount++;
            if (regions[i].size() > 1) {
                cout << "Connected Region " << regionCount << ": ";
            } else {
                cout << "Disconnected Node " << regionCount << ": ";
            }
            for (string nodeName : regions[i]) cout << nodeName << " ";
            cout << endl;
        }
    }

    return 0;
}
