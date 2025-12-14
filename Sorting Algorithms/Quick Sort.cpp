#include <iostream>
using namespace std;

// Function to partition the array
int Partition(int activityScore[], int l, int r) {
    int pivot = activityScore[l];   // Pivot = first activity score
    int i = l;
    int j = r + 1;

    while (true) {
        // Move i to the right
        do {
            i++;
        } while (i <= r && activityScore[i] <= pivot);

        // Move j to the left
        do {
            j--;
        } while (activityScore[j] > pivot);

        if (i >= j)
            break;

        swap(activityScore[i], activityScore[j]);
    }

    swap(activityScore[l], activityScore[j]);
    return j;
}

// Quick Sort function
void QuickSort(int activityScore[], int l, int r) {
    if (l < r) {
        int s = Partition(activityScore, l, r);
        QuickSort(activityScore, l, s - 1);
        QuickSort(activityScore, s + 1, r);
    }
}

int main() {
    int n;

    cout << "Enter number of tourist activities: ";
    cin >> n;

    int activityScore[n];
    cout << "Enter popularity/time score of each activity:\n";
    for (int i = 0; i < n; i++) {
        cin >> activityScore[i];
    }

    // Apply Quick Sort
    QuickSort(activityScore, 0, n - 1);

    cout << "\nTourist activities ranked using Quick Sort:\n";
    for (int i = 0; i < n; i++) {
        cout << activityScore[i] << " ";
    }
    cout << endl;

    return 0;
}
