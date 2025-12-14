#include <iostream>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

// Node structure for each product-store entry
struct Node {
    string productName;
    string storeID;
    Node* next;

    Node(string p, string s) {
        productName = p;
        storeID = s;
        next = NULL;
    }
};

class HashTable {
private:
    Node* table[TABLE_SIZE];

    // Simple hash function based on product name length
    int hashFunction(const string& key) {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i)
            table[i] = NULL;
    }

    // Insert product availability
    void insert(const string& productName, const string& storeID) {
        int hashKey = hashFunction(productName);
        Node* newNode = new Node(productName, storeID);

        if (table[hashKey] == NULL) {
            table[hashKey] = newNode;
        } else {
            Node* temp = table[hashKey];
            while (temp->next != NULL) {
                if (temp->productName == productName && temp->storeID == storeID) {
                    delete newNode; // Already exists
                    return;
                }
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Search for product in a specific store
    void search(const string& productName, const string& storeID) {
        int hashKey = hashFunction(productName);
        Node* temp = table[hashKey];
        while (temp != NULL) {
            if (temp->productName == productName && temp->storeID == storeID) {
                cout << "Product '" << productName << "' is available in Store " << storeID << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Product '" << productName << "' NOT found in Store " << storeID << endl;
    }

    // Remove product availability entry
    void remove(const string& productName, const string& storeID) {
        int hashKey = hashFunction(productName);
        Node* temp = table[hashKey];
        Node* prev = NULL;

        while (temp != NULL && !(temp->productName == productName && temp->storeID == storeID)) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Product '" << productName << "' not found in Store " << storeID << endl;
            return;
        }

        if (prev == NULL)
            table[hashKey] = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Product '" << productName << "' removed from Store " << storeID << endl;
    }
};

int main() {
    HashTable productTable;
    int choice;
    string productName, storeID;

    do {
        cout << "\nProduct Availability Menu:\n";
        cout << "1. Add Product Availability\n2. Check Product Availability\n3. Remove Product Availability\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Product Name: ";
                cin >> productName;
                cout << "Enter Store ID: ";
                cin >> storeID;
                productTable.insert(productName, storeID);
                cout << "Product added successfully.\n";
                break;

            case 2:
                cout << "Enter Product Name to search: ";
                cin >> productName;
                cout << "Enter Store ID: ";
                cin >> storeID;
                productTable.search(productName, storeID);
                break;

            case 3:
                cout << "Enter Product Name to remove: ";
                cin >> productName;
                cout << "Enter Store ID: ";
                cin >> storeID;
                productTable.remove(productName, storeID);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
