#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Number of areas
int numAreas = 3;

// Graph representing connectivity between areas (adjacency matrix)
int areaGraph[10][10] = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}
};

int visitedArea[10];

// Names of areas
string areaNames[10] = {"Downtown", "OldTown", "Seaside"};

// Attractions in each area
vector<string> attractions[10] = {
    {"Museum", "Art Gallery"},         // Downtown
    {"Park", "Zoo", "Aquarium"},       // OldTown
    {"Beach", "Lighthouse"}            // Seaside
};

// DFS to explore attractions in an area and move to connected areas
void exploreArea(int area) {
    visitedArea[area] = 1;
    cout << "Exploring " << areaNames[area] << ":\n";

    // Deeply visit all attractions in this area
    for (string attr : attractions[area]) {
        cout << "  Visiting " << attr << endl;
    }

    // Move to connected areas
    for (int i = 0; i < numAreas; i++) {
        if (areaGraph[area][i] == 1 && visitedArea[i] == 0) {
            cout << "\nMoving from " << areaNames[area] << " to " << areaNames[i] << "...\n";
            exploreArea(i);
            cout << "Returning to " << areaNames[area] << "...\n";
        }
    }
}

int main() {
    for (int i = 0; i < numAreas; i++) visitedArea[i] = 0;

    string startAreaName;
    cout << "Choose your starting area (Downtown, OldTown, Seaside): ";
    cin >> startAreaName;

    // Map area name to index
    int startArea = -1;
    for (int i = 0; i < numAreas; i++) {
        if (startAreaName == areaNames[i]) {
            startArea = i;
            break;
        }
    }

    if (startArea == -1) {
        cout << "Invalid area name entered!\n";
        return 0;
    }

    cout << "\nStarting deep exploration from " << areaNames[startArea] << "...\n\n";
    exploreArea(startArea);

    cout << "\nTourism exploration completed.\n";
    return 0;
}
