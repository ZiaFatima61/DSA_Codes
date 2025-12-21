#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to;
    double loss; // Power loss in MW (can be negative for faults)
    string name; // Transmission line name
};

// Bellman-Ford to compute min power loss and detect negative cycles
bool bellmanFord(int substations, int source, vector<Edge>& edges, vector<double>& minLoss, vector<int>& parent, vector<int>& lastEdge) {
    const double INF = numeric_limits<double>::infinity();
    minLoss.assign(substations, INF);
    parent.assign(substations, -1);
    lastEdge.assign(substations, -1);
    minLoss[source] = 0;

    // Relax edges |V|-1 times
    for (int i = 0; i < substations - 1; i++) {
        for (int j = 0; j < edges.size(); j++) {
            Edge e = edges[j];
            if (minLoss[e.from] != INF && minLoss[e.from] + e.loss < minLoss[e.to]) {
                minLoss[e.to] = minLoss[e.from] + e.loss;
                parent[e.to] = e.from;
                lastEdge[e.to] = j;
            }
        }
    }

    // Check for negative cycles
    for (int j = 0; j < edges.size(); j++) {
        Edge e = edges[j];
        if (minLoss[e.from] != INF && minLoss[e.from] + e.loss < minLoss[e.to]) {
            // Negative cycle detected
            int y = e.to;
            for (int i = 0; i < substations; i++) y = parent[y]; // move inside the cycle

            // Reconstruct the cycle
            vector<int> cycle;
            vector<string> cycleEdges;
            int start = y;
            do {
                cycle.push_back(start);
                cycleEdges.push_back(edges[lastEdge[start]].name);
                start = parent[start];
            } while (start != y);
            cycle.push_back(y);
            reverse(cycle.begin(), cycle.end());
            reverse(cycleEdges.begin(), cycleEdges.end());

            cout << "\nALERT: Power fluctuation detected! Negative cycle exists:\n";
            for (int i = 0; i < cycleEdges.size(); i++) {
                cout << "Substation " << cycle[i] << " --[" << cycleEdges[i] << "]--> ";
            }
            cout << "Substation " << cycle.back() << endl;
            cout << "Check these lines for abnormal feedback!\n";
            return true;
        }
    }

    return false;
}

int main() {
    int substations, lines;
    cout << "Enter number of substations and transmission lines: ";
    cin >> substations >> lines;

    vector<Edge> edges(lines);
    cin.ignore();
    cout << "Enter transmission lines (from to loss_MW line_name):\n";
    for (int i = 0; i < lines; i++) {
        string lineName;
        cin >> edges[i].from >> edges[i].to >> edges[i].loss;
        cin.ignore();
        getline(cin, edges[i].name);
    }

    int source;
    cout << "Enter main power station index: ";
    cin >> source;

    vector<double> minLoss;
    vector<int> parent, lastEdge;
    bool hasFluctuation = bellmanFord(substations, source, edges, minLoss, parent, lastEdge);

    if (!hasFluctuation) {
        cout << fixed << setprecision(2);
        cout << "\nGrid status: No negative cycles detected.\n";
        cout << "Minimum power loss from source substation " << source << ":\n";
        cout << "Substation\tMin Loss (MW)\tPath from Source\n";

        for (int i = 0; i < substations; i++) {
            if (minLoss[i] == numeric_limits<double>::infinity()) {
                cout << i << "\t\tINF\t\tNo path\n";
            } else {
                vector<int> path;
                vector<string> pathEdges;
                int v = i;
                while (v != source && v != -1) {
                    path.push_back(v);
                    pathEdges.push_back(edges[lastEdge[v]].name);
                    v = parent[v];
                }
                path.push_back(source);
                reverse(path.begin(), path.end());
                reverse(pathEdges.begin(), pathEdges.end());

                cout << i << "\t\t" << minLoss[i] << "\t\t";
                for (int j = 0; j < pathEdges.size(); j++) {
                    cout << path[j] << " --[" << pathEdges[j] << "]--> ";
                }
                cout << path.back() << endl;
            }
        }
    }

    return 0;
}
