#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure representing a forest node
struct ForestNode {
    string zoneName;
    int temperature;
    int smokeLevel;
    int spreadSpeed;
    int priority;   // Higher = more dangerous
};

class PriorityQueue {
private:
    vector<ForestNode> heap;

    void heapify(int k) {
        int n = heap.size();
        while (2 * k + 1 < n) {
            int j = 2 * k + 1;
            if (j + 1 < n && heap[j].priority < heap[j + 1].priority)
                j++;

            if (heap[k].priority >= heap[j].priority)
                break;

            swap(heap[k], heap[j]);
            k = j;
        }
    }

public:
    void insert(ForestNode node) {
        heap.push_back(node);
        int k = heap.size() - 1;

        while (k > 0 && heap[k].priority > heap[(k - 1) / 2].priority) {
            swap(heap[k], heap[(k - 1) / 2]);
            k = (k - 1) / 2;
        }
    }

    ForestNode removeTop() {
        if (heap.empty()) {
            cout << "Priority Queue is empty!\n";
            return {};
        }

        ForestNode maxNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return maxNode;
    }

    ForestNode top() {
        if (!heap.empty())
            return heap[0];
        return {};
    }

    void printQueue() {
        if (heap.empty()) {
            cout << "Priority Queue is empty!\n";
            return;
        }

        for (auto &node : heap) {
            cout << node.zoneName
                 << " (Priority: " << node.priority << ")  ";
        }
        cout << endl;
    }

    bool isEmpty() {
        return heap.empty();
    }
};

int main() {
    PriorityQueue pq;
    int choice;

    while (1) {
        cout << "\nSmart Forest Fire Detection - Priority Queue\n";
        cout << "1. Add forest zone data\n";
        cout << "2. Process highest risk zone\n";
        cout << "3. View highest risk zone\n";
        cout << "4. Display all zones\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                ForestNode node;
                cout << "Enter Zone Name: ";
                cin >> node.zoneName;

                cout << "Enter Temperature: ";
                cin >> node.temperature;

                cout << "Enter Smoke Level: ";
                cin >> node.smokeLevel;

                cout << "Enter Fire Spread Speed: ";
                cin >> node.spreadSpeed;

                node.priority = node.temperature +
                                node.smokeLevel +
                                node.spreadSpeed;

                pq.insert(node);
                cout << "Zone added successfully!\n";
                break;
            }

            case 2: {
                ForestNode node = pq.removeTop();
                if (!node.zoneName.empty()) {
                    cout << "Processing Highest Risk Zone:\n";
                    cout << "Zone: " << node.zoneName
                         << " | Priority: " << node.priority << endl;
                }
                break;
            }

            case 3: {
                ForestNode node = pq.top();
                if (!node.zoneName.empty()) {
                    cout << "Highest Risk Zone:\n";
                    cout << "Zone: " << node.zoneName
                         << " | Priority: " << node.priority << endl;
                }
                break;
            }

            case 4:
                cout << "All Zones in Priority Queue:\n";
                pq.printQueue();
                break;

            case 5:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
