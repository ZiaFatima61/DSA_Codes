#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

// Segment Tree to manage electricity usage
class SegmentTree {
    vector<double> tree;
    int n;

    void build(const vector<double>& usage, int node, int start, int end) {
        if (start == end) {
            tree[node] = usage[start];
        } else {
            int mid = (start + end) / 2;
            build(usage, 2*node, start, mid);
            build(usage, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

    double query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0; // No overlap
        if (l <= start && end <= r) return tree[node]; // Total overlap
        int mid = (start + end) / 2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }

    void update(int node, int start, int end, int idx, double val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) update(2*node, start, mid, idx, val);
            else update(2*node+1, mid+1, end, idx, val);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }

public:
    SegmentTree(const vector<double>& usage) {
        n = usage.size();
        tree.resize(4*n);
        build(usage, 1, 0, n-1);
    }

    double rangeQuery(int l, int r) {
        return query(1, 0, n-1, l, r);
    }

    void pointUpdate(int idx, double val) {
        update(1, 0, n-1, idx, val);
    }
};

int main() {
    int hours;
    cout << "Enter the number of hourly readings for this substation: ";
    cin >> hours;

    vector<double> hourlyUsage(hours);
    cout << "Enter hourly electricity usage in kWh:\n";
    for (int i = 0; i < hours; i++) {
        cout << "Hour " << i << ": ";
        cin >> hourlyUsage[i];
    }

    SegmentTree grid(hourlyUsage);

    int q;
    cout << "\nEnter number of operations (queries/updates): ";
    cin >> q;

    while (q--) {
        cout << "\nSelect operation: 1 = Query total usage, 2 = Update reading: ";
        int op;
        cin >> op;

        if (op == 1) {
            int startHour, endHour;
            cout << "Enter start and end hour (0-indexed): ";
            cin >> startHour >> endHour;
            double total = grid.rangeQuery(startHour, endHour);
            cout << fixed << setprecision(2);
            cout << "Total electricity usage from hour " << startHour
                 << " to " << endHour << " = " << total << " kWh\n";
        } else if (op == 2) {
            int hourIdx;
            double newUsage;
            cout << "Enter hour index to update and new usage in kWh: ";
            cin >> hourIdx >> newUsage;
            grid.pointUpdate(hourIdx, newUsage);
            cout << "Updated hour " << hourIdx << " usage to " << newUsage << " kWh\n";
        } else {
            cout << "Invalid operation. Please choose 1 or 2.\n";
        }
    }

    return 0;
}
