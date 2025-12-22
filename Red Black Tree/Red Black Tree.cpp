#include <iostream>
#include <string>
using namespace std;

enum Color { RED, BLACK };

// Store node
struct Node {
    string storeName;
    int floor;
    string zone;

    Color color;
    Node *left, *right, *parent;

    Node(string name, int f, string z) {
        storeName = name;
        floor = f;
        zone = z;
        color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree {
private:
    Node* root;

    // Left rotation
    void rotateLeft(Node* &pt) {
        Node* pt_right = pt->right;

        pt->right = pt_right->left;
        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    // Right rotation
    void rotateRight(Node* &pt) {
        Node* pt_left = pt->left;

        pt->left = pt_left->right;
        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    // Fix Red-Black Tree violations
    void fixViolation(Node* &pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while (pt != root && pt->color == RED && pt->parent->color == RED) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Parent is left child
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                // Case 1: Uncle is RED
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                // Case 2 & 3
                else {
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateRight(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            // Parent is right child
            else {
                Node* uncle_pt = grand_parent_pt->left;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateLeft(grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    // Insert store
    void insert(string name, int floor, string zone) {
        Node* pt = new Node(name, floor, zone);

        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr) {
            parent = current;
            if (pt->storeName < current->storeName)
                current = current->left;
            else
                current = current->right;
        }

        pt->parent = parent;

        if (parent == nullptr)
            root = pt;
        else if (pt->storeName < parent->storeName)
            parent->left = pt;
        else
            parent->right = pt;

        fixViolation(pt);
    }

    // Search store
    void search(string name) {
        Node* current = root;
        while (current != nullptr) {
            if (name == current->storeName) {
                cout << "Store Found!\n";
                cout << "Name : " << current->storeName << endl;
                cout << "Floor: " << current->floor << endl;
                cout << "Zone : " << current->zone << endl;
                return;
            }
            if (name < current->storeName)
                current = current->left;
            else
                current = current->right;
        }
        cout << "Store not found.\n";
    }
};

int main() {
    RedBlackTree mall;

    // Insert stores
    mall.insert("ZARA", 1, "Fashion Zone");
    mall.insert("NIKE", 1, "Fashion Zone");
    mall.insert("APPLE STORE", 2, "Electronics Zone");
    mall.insert("PVR CINEMAS", 3, "Entertainment Zone");
    mall.insert("MCDONALDS", 0, "Food Court");

    // Search
    cout << "Searching for NIKE:\n";
    mall.search("NIKE");

    return 0;
}

