#include <iostream>
using namespace std;

// Trie Node definition
struct TrieNode {
    TrieNode* children[26];
    int wordCount;

    TrieNode() {
        wordCount = 0;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

// Insert product name into Trie
void insertProduct(TrieNode* root, const string& product) {
    TrieNode* current = root;
    for (char c : product) {
        int index = tolower(c) - 'a'; // case-insensitive
        if (current->children[index] == NULL)
            current->children[index] = new TrieNode();
        current = current->children[index];
    }
    current->wordCount++;
}

// Search for exact product
int searchProduct(TrieNode* root, const string& product) {
    TrieNode* current = root;
    for (char c : product) {
        int index = tolower(c) - 'a';
        if (current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }
    return current->wordCount > 0 ? 1 : 0;
}

// Delete a product
int deleteProduct(TrieNode* root, const string& product) {
    TrieNode* current = root;
    TrieNode* lastBranch = NULL;
    char lastBranchChar;

    for (char c : product) {
        int index = tolower(c) - 'a';
        if (current->children[index] == NULL)
            return 0;

        int childCount = 0;
        for (int i = 0; i < 26; i++)
            if (current->children[i] != NULL)
                childCount++;

        if (childCount > 1) {
            lastBranch = current;
            lastBranchChar = c;
        }
        current = current->children[index];
    }

    int childCount = 0;
    for (int i = 0; i < 26; i++)
        if (current->children[i] != NULL)
            childCount++;

    if (childCount > 0) {
        current->wordCount--;
    } else if (lastBranch) {
        lastBranch->children[lastBranchChar - 'a'] = NULL;
    } else {
        root->children[tolower(product[0]) - 'a'] = NULL;
    }

    return 1;
}

// Display all product names in Trie
void displayProducts(TrieNode* root, string prefix) {
    if (root->wordCount > 0)
        cout << prefix << "\n";

    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            char nextChar = 'a' + i;
            displayProducts(root->children[i], prefix + nextChar);
        }
    }
}

int main() {
    TrieNode* root = new TrieNode();
    int choice;

    while (true) {
        cout << "\nProduct Auto-Suggestion Menu:\n";
        cout << "1. Add product\n2. Search product\n3. Delete product\n4. Display all products\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string product;
            cout << "Enter product name to add: ";
            cin >> product;
            insertProduct(root, product);
            cout << "Product added successfully.\n";
        } 
        else if (choice == 2) {
            string product;
            cout << "Enter product name to search: ";
            cin >> product;
            if (searchProduct(root, product))
                cout << "Product found.\n";
            else
                cout << "Product not found.\n";
        } 
        else if (choice == 3) {
            string product;
            cout << "Enter product name to delete: ";
            cin >> product;
            if (deleteProduct(root, product))
                cout << "Product deleted successfully.\n";
            else
                cout << "Product not found.\n";
        } 
        else if (choice == 4) {
            cout << "All products in the system:\n";
            displayProducts(root, "");
        } 
        else if (choice == 5) {
            cout << "Exiting program.\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
