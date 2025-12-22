#include <iostream>
#include <string>
using namespace std;

struct Contract {
    int shopID;
    string tenant;
    int expiryDate;     // YYYYMMDD
    int duration;       // months
    Contract* left;
    Contract* right;
};

// Create a new node
Contract* createContract(int id, string tenant, int expiry, int duration) {
    Contract* node = new Contract();
    node->shopID = id;
    node->tenant = tenant;
    node->expiryDate = expiry;
    node->duration = duration;
    node->left = node->right = nullptr;
    return node;
}

// Insert contract (BST based on expiry date)
Contract* insertContract(Contract* root, int id, string tenant, int expiry, int duration) {
    if (root == nullptr)
        return createContract(id, tenant, expiry, duration);

    if (expiry < root->expiryDate)
        root->left = insertContract(root->left, id, tenant, expiry, duration);
    else
        root->right = insertContract(root->right, id, tenant, expiry, duration);

    return root;
}

// Search contract by Shop ID
Contract* searchContract(Contract* root, int shopID) {
    if (root == nullptr)
        return nullptr;

    if (root->shopID == shopID)
        return root;

    Contract* found = searchContract(root->left, shopID);
    if (found != nullptr)
        return found;

    return searchContract(root->right, shopID);
}

// Find minimum node (used in delete)
Contract* findMin(Contract* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Delete contract by expiry date (helper)
Contract* deleteByExpiry(Contract* root, int expiry) {
    if (root == nullptr)
        return root;

    if (expiry < root->expiryDate)
        root->left = deleteByExpiry(root->left, expiry);
    else if (expiry > root->expiryDate)
        root->right = deleteByExpiry(root->right, expiry);
    else {
        // Node found
        if (root->left == nullptr) {
            Contract* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Contract* temp = root->left;
            delete root;
            return temp;
        }
        Contract* temp = findMin(root->right);
        root->expiryDate = temp->expiryDate;
        root->shopID = temp->shopID;
        root->tenant = temp->tenant;
        root->duration = temp->duration;
        root->right = deleteByExpiry(root->right, temp->expiryDate);
    }
    return root;
}

// Update / renew contract
Contract* updateContract(Contract* root, int shopID, int newExpiry, int newDuration) {
    Contract* contract = searchContract(root, shopID);
    if (contract == nullptr) {
        cout << "Contract not found.\n";
        return root;
    }

    // Remove old contract (because expiry date changes BST position)
    root = deleteByExpiry(root, contract->expiryDate);

    // Insert updated contract
    root = insertContract(root, shopID, contract->tenant, newExpiry, newDuration);

    cout << "Contract updated successfully.\n";
    return root;
}

// Inorder traversal (sorted by expiry date)
void displayContracts(Contract* root) {
    if (root == nullptr)
        return;

    displayContracts(root->left);
    cout << "Shop ID: " << root->shopID
         << ", Tenant: " << root->tenant
         << ", Expiry: " << root->expiryDate
         << ", Duration: " << root->duration << " months\n";
    displayContracts(root->right);
}

int main() {

    Contract* root = nullptr;

    // Initial contracts
    root = insertContract(root, 101, "ZARA", 20251231, 36);
    root = insertContract(root, 102, "NIKE", 20241115, 24);
    root = insertContract(root, 103, "APPLE STORE", 20261030, 48);
    root = insertContract(root, 104, "H&M", 20240920, 12);
    root = insertContract(root, 105, "STARBUCKS", 20250301, 18);

    cout << "\nContracts Before Update:\n";
    displayContracts(root);

    // Search contract
    cout << "\nSearching contract for Shop ID 102:\n";
    Contract* c = searchContract(root, 102);
    if (c != nullptr) {
        cout << "Found → Tenant: " << c->tenant
             << ", Expiry: " << c->expiryDate << endl;
    }

    // Update contract (renewal)
    root = updateContract(root, 102, 20261115, 36);

    cout << "\nContracts After Update:\n";
    displayContracts(root);

    return 0;
}
