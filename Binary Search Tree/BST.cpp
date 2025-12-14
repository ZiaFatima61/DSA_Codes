#include <iostream>
#include <string>
using namespace std;

// Binary search to find a product
int binarySearch(string arr[], int size, string key) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            return mid;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Simple bubble sort to sort products alphabetically
void bubbleSort(string arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numProducts;
    cout << "Enter the number of products in the shop: ";
    cin >> numProducts;

    string products[numProducts];
    cout << "Enter the product names:\n";
    cin.ignore(); // ignore leftover newline
    for (int i = 0; i < numProducts; i++) {
        getline(cin, products[i]);
    }

    // Sort products alphabetically for binary search
    bubbleSort(products, numProducts);

    cout << "\nSorted product list:\n";
    for (int i = 0; i < numProducts; i++) {
        cout << products[i] << endl;
    }

    string searchProduct;
    cout << "\nEnter the product name to search: ";
    getline(cin, searchProduct);

    int result = binarySearch(products, numProducts, searchProduct);

    if (result != -1) {
        cout << "Product '" << searchProduct << "' found at position " << result + 1 << " in the shop.\n";
    } else {
        cout << "Product '" << searchProduct << "' not found in the shop.\n";
    }

    return 0;
}
