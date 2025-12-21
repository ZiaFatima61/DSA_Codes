#include <iostream>
using namespace std;

// Structure to store visitor data
struct Visitor {
    int visitorID;
    int entryTime; // minutes since opening
};

// Merge two sorted halves
void merge(Visitor arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Visitor L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].entryTime <= R[j].entryTime) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// Merge Sort function
void mergeSort(Visitor arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    cout << "Enter number of visitors: ";
    cin >> n;

    Visitor visitors[n];

    cout << "Enter Visitor ID and Entry Time (in minutes):\n";
    for (int i = 0; i < n; i++) {
        cin >> visitors[i].visitorID >> visitors[i].entryTime;
    }

    mergeSort(visitors, 0, n - 1);

    cout << "\nVisitors Sorted by Entry Time:\n";
    cout << "Visitor ID\tEntry Time\n";
    for (int i = 0; i < n; i++) {
        cout << visitors[i].visitorID << "\t\t" 
             << visitors[i].entryTime << endl;
    }

    return 0;
}
