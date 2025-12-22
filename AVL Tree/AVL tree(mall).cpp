#include <iostream>
#include <string>
using namespace std;

// AVL Tree Node
struct Node {
    int shopID;
    string tenant;
    string category;
    int floor;

    int height;
    Node* left;
    Node* right;
};

// Utility functions
int height(Node* n) {
    return (n == nullptr) ? 0 : n->height;
}

int getBalance(Node* n) {
    return (n == nullptr) ? 0 : height(n->left) - height(n->right);
}

Node* createNode(int id, string tenant, string category, int floor) {
    Node* node = new Node();
    node->shopID = id;
    node->tenant = tenant;
    node->category = category;
    node->floor = floor;
    node->height = 1;
    node->left = node->right = nullptr;
    return node;
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insert into AVL Tree
Node* insert(Node* root, int id, string tenant, string category, int floor) {
    if (root == nullptr)
        return createNode(id, tenant, category, floor);

    if (id < root->shopID)
        root->left = insert(root->left, id, tenant, category, floor);
    else if (id > root->shopID)
        root->right = insert(root->right, id, tenant, category, floor);
    else
        return root; // Duplicate IDs not allowed

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && id < root->left->shopID)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && id > root->right->shopID)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && id > root->left->shopID) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && id < root->right->shopID) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search by Shop ID
Node* search(Node* root, int id) {
    if (root == nullptr || root->shopID == id)
        return root;

    if (id < root->shopID)
        return search(root->left, id);

    return search(root->right, id);
}

// Update tenant details
void update(Node* root, int id, string newTenant, string newCategory, int newFloor) {
    Node* node = search(root, id);
    if (node == nullptr) {
        cout << "Shop not found.\n";
        return;
    }
    node->tenant = newTenant;
    node->category = newCategory;
    node->floor = newFloor;
    cout << "Shop details updated successfully.\n";
}

// Inorder traversal (sorted order)
void display(Node* root) {
    if (root == nullptr)
        return;

    display(root->left);
    cout << "Shop ID: " << root->shopID
         << ", Tenant: " << root->tenant
         << ", Category: " << root->category
         << ", Floor: " << root->floor << endl;
    display(root->right);
}

int main() {

    Node* root = nullptr;

    // Insert shops
    root = insert(root, 105, "STARBUCKS", "Cafe", 0);
    root = insert(root, 102, "NIKE", "Sportswear", 1);
    root = insert(root, 108, "APPLE STORE", "Electronics", 2);
    root = insert(root, 101, "ZARA", "Clothing", 1);
    root = insert(root, 110, "PVR CINEMAS", "Entertainment", 3);

    cout << "Shop Directory (Sorted by Shop ID):\n";
    display(root);

    cout << "\nSearching Shop ID 102:\n";
    Node* s = search(root, 102);
    if (s != nullptr)
        cout << "Found → " << s->tenant << " on Floor " << s->floor << endl;

    cout << "\nUpdating Shop ID 102:\n";
    update(root, 102, "NIKE FLAGSHIP", "Premium Sportswear", 2);

    cout << "\nAfter Update:\n";
    display(root);

    return 0;
}
