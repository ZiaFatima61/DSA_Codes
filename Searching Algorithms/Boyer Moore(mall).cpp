#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define ALPHABET 256   // Total ASCII characters

// Preprocess bad character table
void badCharHeuristic(string pattern, vector<int>& badChar) {
    int m = pattern.length();
    badChar.assign(ALPHABET, -1);

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }
}

// Boyer–Moore search function
void boyerMooreSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> badChar(ALPHABET);
    badCharHeuristic(pattern, badChar);

    bool found = false;
    int shift = 0;

    while (shift <= n - m) {
        int j = m - 1;

        // Compare pattern from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            cout << "Keyword found at position " << shift << endl;
            found = true;

            shift += (shift + m < n) ?
                     m - badChar[text[shift + m]] : 1;
        } else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }

    if (!found)
        cout << "Keyword not found in description/reviews.\n";
}

int main() {

    string productText =
        "This wireless noise cancelling headphone offers excellent battery life. "
        "Many users say the noise cancellation works well even in crowded areas.";

    string keyword;

    cout << "Enter keyword to search: ";
    getline(cin, keyword);

    cout << "\nSearching in product description and reviews...\n";
    boyerMooreSearch(productText, keyword);

    return 0;
}
