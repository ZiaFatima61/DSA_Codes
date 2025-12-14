#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MaxHeap {
private:
    vector<pair<string, int>> heap; // pair<ZoneName, CrowdCount>

    void heapifyDown(int i) {
        int n = heap.size();
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left].second > heap[largest].second)
            largest = left;
        if (right < n && heap[right].second > heap[largest].second)
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i) {
        if (i && heap[(i - 1) / 2].second < heap[i].second) {
            swap(heap[i], heap[(i - 1) / 2]);
            heapifyUp((i - 1) / 2);
        }
    }

public:
    void insert(string zone, int count) {
        heap.push_back({zone, count});
        heapifyUp(heap.size() - 1);
    }

    pair<string, int> getMax() {
        if (!heap.empty())
            return heap[0];
        return {"", -1};
    }

    void removeMax() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void displayHeap() {
        cout << "Zones by crowd count (max first):\n";
        for (auto &p : heap)
            cout << p.first << " : " << p.second << "\n";
    }
};

int main() {
    MaxHeap crowdHeap;
    int choice;
    string zone;
    int count;

    while (true) {
        cout << "\n1. Add/Update Zone Crowd Count\n";
        cout << "2. Show Most Crowded Zone\n";
        cout << "3. Display All Zones\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Zone Name: ";
            cin >> zone;
            cout << "Enter Crowd Count: ";
            cin >> count;
            crowdHeap.insert(zone, count);
            break;
        case 2: {
            auto maxZone = crowdHeap.getMax();
            if (maxZone.second != -1)
                cout << "Most crowded zone: " << maxZone.first << " with " << maxZone.second << " people.\n";
            else
                cout << "No zones available.\n";
            break;
        }
        case 3:
            crowdHeap.displayHeap();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}
