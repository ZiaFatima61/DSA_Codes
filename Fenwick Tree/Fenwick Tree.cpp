#include <iostream>
using namespace std;

int n, productFrequency[20], BIT[20];

class FenwickTree {
public:
    FenwickTree(int n);
    void buildTree();
    void update(int index, int delta);
    int query(int index);
    int totalPurchases();
    int rangeQuery(int left, int right);
};

// Initialize BIT
FenwickTree::FenwickTree(int n) {
    for (int i = 0; i <= n; i++) {
        BIT[i] = 0;
    }
}

// Build BIT with initial purchase data
void FenwickTree::buildTree() {
    cout << "Enter the purchase frequency for each product:\n";
    for (int i = 1; i <= n; i++) {
        cin >> productFrequency[i];
        update(i, productFrequency[i]);
    }
}

// Update purchase frequency of a product
void FenwickTree::update(int index, int delta) {
    for (; index <= n; index += index & -index)
        BIT[index] += delta;
}

// Query cumulative purchases up to product index
int FenwickTree::query(int index) {
    int sum = 0;
    while (index > 0) {
        sum += BIT[index];
        index -= index & -index;
    }
    return sum;
}

// Total purchases of all products
int FenwickTree::totalPurchases() {
    return query(n);
}

// Range query: total purchases from product left to right
int FenwickTree::rangeQuery(int left, int right) {
    return query(right) - query(left - 1);
}

int main() {
    cout << "Enter the number of products: ";
    cin >> n;

    FenwickTree ft(n);
    ft.buildTree();

    cout << "Total purchases across all products: " << ft.totalPurchases() << endl;

    int l, r;
    cout << "\nEnter range of products to query (left right): ";
    cin >> l >> r;

    cout << "Total purchases from product " << l << " to " << r << " = "
         << ft.rangeQuery(l, r) << endl;

    return 0;
}
