#include <iostream>
#include <vector>
using namespace std;

class ShopPriorityQueue {
private:
    vector<int> heap;   // Stores shop priority score

    void heapify(int k)
    {
        int n = heap.size();
        bool isHeap = false;

        while (!isHeap && 2 * k + 1 < n)
        {
            int j = 2 * k + 1; // left child

            if (j + 1 < n && heap[j] < heap[j + 1])
                j++; // choose larger child

            if (heap[k] >= heap[j])
                isHeap = true;
            else
            {
                swap(heap[k], heap[j]);
                k = j;
            }
        }
    }

public:
    ShopPriorityQueue() {}

    // Insert shop with priority score
    void insertShop(int priorityScore)
    {
        heap.push_back(priorityScore);
        int k = heap.size() - 1;

        while (k > 0 && heap[k] > heap[(k - 1) / 2])
        {
            swap(heap[k], heap[(k - 1) / 2]);
            k = (k - 1) / 2;
        }
    }

    // Allocate best available shop
    int allocateShop()
    {
        if (heap.empty())
        {
            cout << "No shops available for allocation!" << endl;
            return -1;
        }

        int bestShop = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);

        return bestShop;
    }

    int viewBestShop()
    {
        if (!heap.empty())
            return heap[0];
        return -1;
    }

    void displayShops()
    {
        if (heap.empty())
        {
            cout << "No shops in the queue!" << endl;
            return;
        }

        cout << "Shop Priority Queue: ";
        for (int score : heap)
            cout << score << " ";
        cout << endl;
    }

    bool isEmpty()
    {
        return heap.empty();
    }
};

int main() {
    ShopPriorityQueue pq;
    int choice, priority;

    while (true)
    {
        cout << "\n--- Automated Shop Allocation System ---\n";
        cout << "1. Add shop (priority score)\n";
        cout << "2. Allocate best available shop\n";
        cout << "3. View best shop\n";
        cout << "4. Display all shops\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter shop priority score (based on demand/footfall/rent): ";
                cin >> priority;
                pq.insertShop(priority);
                cout << "Shop added successfully.\n";
                break;

            case 2:
                priority = pq.allocateShop();
                if (priority != -1)
                    cout << "Allocated shop with priority score: " << priority << endl;
                break;

            case 3:
                priority = pq.viewBestShop();
                if (priority != -1)
                    cout << "Best available shop priority score: " << priority << endl;
                break;

            case 4:
                pq.displayShops();
                break;

            case 5:
                cout << "Exiting shop allocation system.\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
