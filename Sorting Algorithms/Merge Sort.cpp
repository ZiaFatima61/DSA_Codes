#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    string brand;
    double price;
    int popularity; // Higher value = more popular
};

// Merge function for products
void Merge(Product B[], int p, Product C[], int q, Product A[], int criteria) {
    int i = 0, j = 0, k = 0;

    while (i < p && j < q) {
        bool condition = false;
        if (criteria == 1) // Price ascending
            condition = B[i].price <= C[j].price;
        else if (criteria == 2) // Brand alphabetical
            condition = B[i].brand <= C[j].brand;
        else if (criteria == 3) // Popularity descending
            condition = B[i].popularity >= C[j].popularity;

        if (condition) {
            A[k++] = B[i++];
        } else {
            A[k++] = C[j++];
        }
    }

    while (i < p) A[k++] = B[i++];
    while (j < q) A[k++] = C[j++];
}

// MergeSort function for products
void MergeSort(Product A[], int n, int criteria) {
    if (n > 1) {
        int mid = n / 2;
        Product B[mid];
        Product C[n - mid];

        for (int i = 0; i < mid; i++) B[i] = A[i];
        for (int i = mid; i < n; i++) C[i - mid] = A[i];

        MergeSort(B, mid, criteria);
        MergeSort(C, n - mid, criteria);

        Merge(B, mid, C, n - mid, A, criteria);
    }
}

int main() {
    int n;
    cout << "Enter number of products: ";
    cin >> n;
    cin.ignore();

    Product products[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter product name: ";
        getline(cin, products[i].name);
        cout << "Enter brand: ";
        getline(cin, products[i].brand);
        cout << "Enter price: ";
        cin >> products[i].price;
        cout << "Enter popularity (higher is better): ";
        cin >> products[i].popularity;
        cin.ignore();
    }

    int criteria;
    cout << "Sort by:\n1. Price\n2. Brand\n3. Popularity\nEnter choice: ";
    cin >> criteria;

    MergeSort(products, n, criteria);

    cout << "\nSorted Products:\n";
    for (int i = 0; i < n; i++) {
        cout << products[i].name << " | " << products[i].brand << " | "
             << products[i].price << " | " << products[i].popularity << endl;
    }

    return 0;
}
