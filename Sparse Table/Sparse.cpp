#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of days: ";
    cin >> n;

    vector<int> sales(n);
    cout << "Enter daily sales:\n";
    for (int i = 0; i < n; i++)
        cin >> sales[i];

    // Build Sparse Table for Range Maximum Query
    int K = log2(n) + 1;
    vector<vector<int>> st(n, vector<int>(K));

    // Initialize first column
    for (int i = 0; i < n; i++)
        st[i][0] = sales[i];

    // Build rest of the table
    for (int j = 1; j < K; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }

    // Precompute logarithms
    vector<int> logTable(n + 1);
    logTable[1] = 0;
    for (int i = 2; i <= n; i++)
        logTable[i] = logTable[i/2] + 1;

    // Query loop
    int q;
    cout << "Enter number of queries: ";
    cin >> q;
    cout << "Enter queries (l r) for range of days (0-indexed):\n";
    while (q--) {
        int l, r;
        cin >> l >> r;

        int j = logTable[r - l + 1];
        int maxSales = max(st[l][j], st[r - (1 << j) + 1][j]);
        cout << "Maximum sales from day " << l << " to day " << r << " = " << maxSales << "\n";
    }

    return 0;
}
