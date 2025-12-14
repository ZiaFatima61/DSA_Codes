#include <iostream>
using namespace std;


// Partition function
int partition(int activities[], int low, int high) {
    int pivot = activities[low];
    int i = low;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (i <= high && activities[i] <= pivot);

        do {
            j--;
        } while (activities[j] > pivot);

        if (i >= j)
            break;

        swap(activities[i], activities[j]);
    }

    swap(activities[low], activities[j]);
    return j;
}

// Quick Sort function
void quickSort(int activities[], int low, int high) {
    if (low < high) {
        int p = partition(activities, low, high);
        quickSort(activities, low, p - 1);
        quickSort(activities, p + 1, high);
    }
}


int binarySearch(int activities[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (activities[mid] == key)
            return mid;
        else if (activities[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}


int main() {
    int n;
    cout << "Enter number of tourist activities: ";
    cin >> n;

    int activities[n];
    cout << "Enter popularity/time score of each activity:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i];
    }

    // Step 1: Sort activities using Quick Sort
    quickSort(activities, 0, n - 1);

    cout << "\nSorted tourist activities (ranked): ";
    for (int i = 0; i < n; i++) {
        cout << activities[i] << " ";
    }

    // Step 2: Search using Binary Search
    int preference;
    cout << "\n\nEnter preferred activity score to search: ";
    cin >> preference;

    int result = binarySearch(activities, n, preference);

    if (result != -1)
        cout << "Tourist activity found at position: " << result << endl;
    else
        cout << "No matching tourist activity found.\n";

    return 0;
}
