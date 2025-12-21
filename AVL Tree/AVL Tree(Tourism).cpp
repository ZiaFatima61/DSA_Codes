#include <iostream>
#include <string>
using namespace std;

// AVL Tree Node for hotels
struct HotelNode {
    string name;
    int price;
    HotelNode* left;
    HotelNode* right;
    int height;
};

// Utility functions
int height(HotelNode* node) { return node ? node->height : 0; }
HotelNode* createNode(string name, int price) {
    HotelNode* node = new HotelNode();
    node->name = name;
    node->price = price;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}
int getBalance(HotelNode* node) { return node ? height(node->left) - height(node->right) : 0; }

// Rotations
HotelNode* rightRotate(HotelNode* y) {
    HotelNode* x = y->left;
    HotelNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
HotelNode* leftRotate(HotelNode* x) {
    HotelNode* y = x->right;
    HotelNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Insert a hotel
HotelNode* insertHotel(HotelNode* root, string name, int price) {
    if (!root) return createNode(name, price);
    if (price < root->price) root->left = insertHotel(root->left, name, price);
    else root->right = insertHotel(root->right, name, price);

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // AVL balancing
    if (balance > 1 && price < root->left->price) return rightRotate(root);
    if (balance < -1 && price > root->right->price) return leftRotate(root);
    if (balance > 1 && price > root->left->price) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (balance < -1 && price < root->right->price) { root->right = rightRotate(root->right); return leftRotate(root); }

    return root;
}

// In-order traversal (sorted by price)
void showHotels(HotelNode* root) {
    if (!root) return;
    showHotels(root->left);
    cout << root->name << " - $" << root->price << endl;
    showHotels(root->right);
}

// Budget search
void searchBudget(HotelNode* root, int budget) {
    if (!root) return;
    searchBudget(root->left, budget);
    if (root->price <= budget) cout << root->name << " - $" << root->price << endl;
    searchBudget(root->right, budget);
}

int main() {
    const int numAreas = 3;
    string areas[numAreas] = {"Downtown", "Seaside", "OldTown"};
    HotelNode* areaHotels[numAreas] = {nullptr};

    // Sample hotels for each area
    areaHotels[0] = insertHotel(areaHotels[0], "Sunshine Resort", 120);
    areaHotels[0] = insertHotel(areaHotels[0], "Budget Inn", 80);
    areaHotels[0] = insertHotel(areaHotels[0], "Luxury Suites", 200);

    areaHotels[1] = insertHotel(areaHotels[1], "Sea View Hotel", 150);
    areaHotels[1] = insertHotel(areaHotels[1], "Ocean Breeze", 100);

    areaHotels[2] = insertHotel(areaHotels[2], "Comfort Stay", 90);
    areaHotels[2] = insertHotel(areaHotels[2], "Historic Inn", 130);

    string chosenArea;
    cout << "Enter the area you want to explore (Downtown, Seaside, OldTown): ";
    cin >> chosenArea;

    int areaIndex = -1;
    for (int i = 0; i < numAreas; i++) {
        if (chosenArea == areas[i]) {
            areaIndex = i;
            break;
        }
    }

    if (areaIndex == -1) {
        cout << "Invalid area name!\n";
        return 0;
    }

    cout << "\nHotels in " << chosenArea << " sorted by price:\n";
    showHotels(areaHotels[areaIndex]);

    int budget;
    cout << "\nEnter your budget: $";
    cin >> budget;

    cout << "Hotels within budget $" << budget << ":\n";
    searchBudget(areaHotels[areaIndex], budget);

    return 0;
}
