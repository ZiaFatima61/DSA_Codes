#include <iostream>
#include <map>
#include <string>

using namespace std;

// Store details
struct Store {
    string name;
    int floor;
    string zone;
    string category;
};

int main() {

    // Red-Black Tree (internally used by std::map)
    map<int, Store> mallDirectory;

    // Adding stores (opening new shops)
    mallDirectory[101] = {"ZARA", 1, "Fashion Zone", "Clothing"};
    mallDirectory[102] = {"NIKE", 1, "Fashion Zone", "Sportswear"};
    mallDirectory[201] = {"APPLE STORE", 2, "Electronics Zone", "Gadgets"};
    mallDirectory[301] = {"PVR CINEMAS", 3, "Entertainment Zone", "Cinema"};
    mallDirectory[150] = {"McDonald's", 0, "Food Court", "Restaurant"};

    // Fast store lookup
    int searchID = 102;
    if (mallDirectory.find(searchID) != mallDirectory.end()) {
        Store s = mallDirectory[searchID];
        cout << "Store Found:\n";
        cout << "Name: " << s.name
             << ", Floor: " << s.floor
             << ", Zone: " << s.zone << endl;
    }

    // 📋 Display all stores (sorted automatically)
    cout << "\nMall Store Directory:\n";
    for (auto &entry : mallDirectory) {
        cout << "Store ID: " << entry.first
             << ", Name: " << entry.second.name
             << ", Floor: " << entry.second.floor
             << ", Zone: " << entry.second.zone
             << ", Category: " << entry.second.category << endl;
    }

    // Remove a store (shop closed)
    mallDirectory.erase(150); // McDonald's closed

    cout << "\nAfter Store Closure:\n";
    for (auto &entry : mallDirectory) {
        cout << entry.second.name << " on Floor "
             << entry.second.floor << endl;
    }

    return 0;
}
