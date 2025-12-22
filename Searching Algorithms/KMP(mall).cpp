#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Build LPS array
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int length = 0;
    int i = 1;
    int m = pattern.size();
    lps[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search function
vector<int> KMPSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);
    vector<int> positions;

    computeLPSArray(pattern, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return positions;
}

int main() {
    vector<string> catalog = {
        "Apple iPhone 15 Pro",
        "Samsung Galaxy S24 Ultra",
        "Nike Air Max 2025",
        "Sony WH-1000XM5 Headphones",
        "Dell XPS 15 Laptop",
        "Apple MacBook Pro 16",
        "Canon EOS R5 Camera"
    };

    string keyword;
    cout << "Enter product name to search: ";
    getline(cin, keyword);

    cout << "\nSearching in product catalog...\n\n";

    bool found = false;
    for (int i = 0; i < catalog.size(); i++) {
        vector<int> pos = KMPSearch(catalog[i], keyword);
        if (!pos.empty()) {
            found = true;
            cout << "Found in catalog item " << i + 1 << ": " << catalog[i] << endl;
        }
    }

    if (!found)
        cout << "Product not found in catalog.\n";

    return 0;
}
