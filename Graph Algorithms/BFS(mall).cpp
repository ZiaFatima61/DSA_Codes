#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS to find shortest path on a floor
void bfsShortestPath(int graph[10][10], int locations, int source, int dest) {
    int visited[10] = {0};
    int previous[10];
    for(int i=0;i<locations;i++) previous[i]=-1;

    queue<int> q;
    visited[source] = 1;
    q.push(source);

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        if(u == dest) break; // Stop when destination is reached

        for(int i = 0; i < locations; i++) {
            if(graph[u][i] == 1 && !visited[i]) {
                visited[i] = 1;
                previous[i] = u;
                q.push(i);
            }
        }
    }

    // Reconstruct path
    if(!visited[dest]) {
        cout << "No path exists from Sensor " << source << " to Sensor " << dest << endl;
        return;
    }

    vector<int> path;
    for(int at = dest; at != -1; at = previous[at])
        path.push_back(at);

    cout << "Shortest path from Sensor " << source << " to Sensor " << dest << ": ";
    for(int i = path.size()-1; i >= 0; i--)
        cout << "Sensor " << path[i] << (i>0 ? " -> " : "\n");
}

int main() {
    int locations = 5;

    // Adjacency matrix for floor layout
    int mallGraph[10][10] = {
        {0,1,1,0,0},
        {1,0,0,1,1},
        {1,0,0,0,1},
        {0,1,0,0,0},
        {0,1,1,0,0}
    };

    int start, end;
    cout << "Enter source location index (e.g., entrance): ";
    cin >> start;
    cout << "Enter destination location index: ";
    cin >> end;

    bfsShortestPath(mallGraph, locations, start, end);

    return 0;
}
