

#include <iostream>
using namespace std;

// Function to construct a heap from the bottom up
void HeapBottomUp(int H[], int n) 
{
    for (int i = n / 2; i >= 1; i--) 
    {
        int k = i;
        int v = H[k];
        int heap = 0; 

        while (heap == 0 && 2 * k <= n) 
        {
            int j = 2 * k;
            if (j < n && H[j] < H[j + 1])
            {
                j = j + 1;
            }

            if (v >= H[j])
            {
                heap = 1;
            } else {
                H[k] = H[j];
                k = j;
            }
        }
        H[k] = v;
    }
}

// Function to delete the maximum element (root) and restore the heap
void DeleteMax(int H[], int& n)
{
    swap(H[1], H[n]);
    n--;
    int k = 1;
    int v = H[k];
    int heap = 0; 

    while (heap == 0 && 2 * k <= n) 
    {
        int j = 2 * k;
        if (j < n && H[j] < H[j + 1]) 
        {
            j = j + 1;
        }

        if (v >= H[j])
        {
            heap = 1;
        }
        else 
        {
            H[k] = H[j];
            k = j;
        }
    }
    H[k] = v;
}

// Heap Sort function
void HeapSort(int H[], int n) 
{
    HeapBottomUp(H, n);
    for (int i = n; i > 1; i--) 
    {
        DeleteMax(H, n);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int H[n + 1]; 
    cout << "Enter the elements: ";
    for (int i = 1; i <= n; i++)
    {
        cin >> H[i];
    }
    HeapSort(H, n);
    cout << "Sorted elements: ";
    for (int i = 1; i <= n; i++)
    {
        cout << H[i] << " ";
    }
    cout << endl;

    return 0;
}
