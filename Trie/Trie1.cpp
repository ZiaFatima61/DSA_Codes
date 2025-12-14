#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Trie Node for shops/facilities
struct TrieNode {
    TrieNode* children[26];
    bool isShop; // true if node represents end of shop/facility name

    TrieNode() {
        isShop = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

// Insert shop/facility name into Trie
void insertShop(TrieNode* root, const string& name) {
    TrieNode* current = root;
    for (char c : name) {
        if (!isalpha(c)) continue; // ignore non-alphabetic characters
        int index = tolower(c) - 'a';
        if (current->children[index] == nullptr)
            current->children[index] = new TrieNode();
        current = current->children[index];
    }
    current->isShop = true;
}

// Search exact shop/facility name
bool searchShop(TrieNode* root, const string& name) {
    TrieNode* current = root;
    for (char c : name) {
        if (!isalpha(c)) continue;
        int index = tolower(c) - 'a';
        if (current->children[index] == nullptr)
            return false;
        current = current->children[index];
    }
    return current->isShop;
}

// Recursive function to display suggestions based on prefix
void suggestShops(TrieNode* root, string prefix) {
    if (root->isShop)
        cout << prefix << "\n";

    for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
            char nextChar = 'a' + i;
            suggestShops(root->children[i], prefix + nextChar);
        }
    }
}

// Display shops that start with a given prefix
void displaySuggestions(TrieNode* root, const string& prefix) {
    TrieNode* current = root;
    for (char c : prefix) {
        if (!isalpha(c)) continue;
        int index = tolower(c) - 'a';
        if (current->children[index] == nullptr) {
            cout << "No suggestions found for prefix \"" << prefix << "\".\n";
            return;
        }
        current = current->children[index];
    }
    cout << "Suggestions for prefix \"" << prefix << "\":\n";
    suggestShops(current, prefix);
}

// Delete a shop/facility from Trie
bool deleteShop(TrieNode* root, const string& name, int depth = 0) {
    if (!root) return false;

    if (depth == name.size()) {
        if (root->isShop)
            root->isShop = false;

        for (int i = 0; i < 26; i++)
            if (root->children[i]) return false;

        return true; // safe to delete this node
    }

    if (!isalpha(name[depth])) return deleteShop(root, name, depth + 1);

    int index = tolower(name[depth]) - 'a';
    if (deleteShop(root->children[index], name, depth + 1)) {
        delete root->children[index];
        root->children[index] = nullptr;

        return !root->isShop && all_of(begin(root->children), end(root->children), [](TrieNode* n){ return n == nullptr; });
    }

    return false;
}

int main() {
    TrieNode* root = new TrieNode();
    int choice;
    string name, prefix;

    while (true) {
        cout << "\nShop Finder Menu:\n";
        cout << "1. Add Shop/Facility\n2. Search Shop\n3. Delete Shop\n4. Display Suggestions\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore();
                cout << "Enter shop/facility name to add: ";
                getline(cin, name);
                insertShop(root, name);
                cout << "Shop/Facility added successfully.\n";
                break;

            case 2:
                cin.ignore();
                cout << "Enter shop/facility name to search: ";
                getline(cin, name);
                if (searchShop(root, name))
                    cout << "Shop/Facility found.\n";
                else
                    cout << "Shop/Facility not found.\n";
                break;

            case 3:
                cin.ignore();
                cout << "Enter shop/facility name to delete: ";
                getline(cin, name);
                deleteShop(root, name);
                cout << "Shop/Facility deletion attempted.\n";
                break;

            case 4:
                cin.ignore();
                cout << "Enter prefix to search suggestions: ";
                getline(cin, prefix);
                displaySuggestions(root, prefix);
                break;

            case 5:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
