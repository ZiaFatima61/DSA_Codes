#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Product {
    string name;
    int trendingScore;
};

// Heapify for max-heap
void heapify(vector<Product> &H, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && H[left].trendingScore > H[largest].trendingScore)
        largest = left;

    if (right < n && H[right].trendingScore > H[largest].trendingScore)
        largest = right;

    if (largest != i) {
        swap(H[i], H[largest]);
        heapify(H, n, largest);
    }
}

// Build heap bottom-up
void buildHeap(vector<Product> &H) {
    int n = H.size();
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(H, n, i);
}

// Heap Sort
void heapSort(vector<Product> &H) {
    int n = H.size();
    buildHeap(H);
    for (int i = n - 1; i >= 1; i--) {
        swap(H[0], H[i]);
        heapify(H, i, 0);
    }
}

// Display top-k trending products
void displayTopK(vector<Product> &H, int k) {
    cout << "\nTop " << k << " Trending Products:\n";
    for (int i = H.size() - 1; i >= H.size() - k && i >=0; i--) {
        cout << H[i].name << " (Score: " << H[i].trendingScore << ")\n";
    }
}

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;
    cin.ignore();

    vector<Product> products(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter product name: ";
        getline(cin, products[i].name);
        cout << "Enter trending score: ";
        cin >> products[i].trendingScore;
        cin.ignore();
    }

    heapSort(products);

    int k;
    cout << "\nEnter number of top trending products to display: ";
    cin >> k;

    displayTopK(products, k);

    return 0;
}
