#include <iostream>
#include <chrono>
#include <vector>
using namespace std;

// ==================== HEAP SORT ====================
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ==================== MERGE SORT ====================
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Wrapper for merge sort
void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

// ==================== UTILITY FUNCTIONS ====================
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Copy arrays to avoid modifying originals
void copyArray(int dest[], const int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    const int n = 1000;

    // Base arrays
    int ascArrBase[n], descArrBase[n];

    // Fill base arrays
    for (int i = 0; i < n; i++) {
        ascArrBase[i] = i + 1;      // 1, 2, 3, ..., 1000
        descArrBase[i] = n - i;     // 1000, 999, 998, ..., 1
    }

    // Working arrays (copies)
    int ascArrHS[n], descArrHS[n];
    int ascArrMS[n], descArrMS[n];

    int choice;

    cout << "===== Heap Sort vs Merge Sort Comparison =====\n";
    cout << "1. Heap Sort (Input array in descending order)\n";
    cout << "2. Heap Sort (Input array in ascending order)\n";
    cout << "3. Merge Sort (Input array in descending order)\n";
    cout << "4. Merge Sort (Input array in ascending order)\n";
    cout << "Enter choice: ";
    cin >> choice;

    chrono::high_resolution_clock::time_point start, end;
    chrono::microseconds duration(0);

    switch (choice) {
        case 1:
            copyArray(descArrHS, descArrBase, n);
            cout << "\nOriginal descending array (first 20 elements):\n";
            printArray(descArrHS, min(20,n));

            start = chrono::high_resolution_clock::now();
            heapSort(descArrHS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Heap Sort (first 20 elements):\n";
            printArray(descArrHS, min(20,n));
            break;

        case 2:
            copyArray(ascArrHS, ascArrBase, n);
            cout << "\nOriginal ascending array (first 20 elements):\n";
            printArray(ascArrHS, min(20,n));

            start = chrono::high_resolution_clock::now();
            heapSort(ascArrHS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Heap Sort (first 20 elements):\n";
            printArray(ascArrHS, min(20,n));
            break;

        // MERGE SORT on descending array
        case 3:
            copyArray(descArrMS, descArrBase, n);
            cout << "\nOriginal descending array (first 20 elements):\n";
            printArray(descArrMS, min(20,n));

            start = chrono::high_resolution_clock::now();
            mergeSortWrapper(descArrMS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Merge Sort (first 20 elements):\n";
            printArray(descArrMS, min(20,n));
            break;

        // MERGE SORT on ascending array
        case 4:
            copyArray(ascArrMS, ascArrBase, n);
            cout << "\nOriginal ascending array (first 20 elements):\n";
            printArray(ascArrMS, min(20,n));

            start = chrono::high_resolution_clock::now();
            mergeSortWrapper(ascArrMS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Merge Sort (first 20 elements):\n";
            printArray(ascArrMS, min(20,n));
            break;

        default:
            cout << "Invalid choice.\n";
            return 0;
    }

    if (choice >= 1 && choice <= 4) {
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "\nTime taken: " << duration.count() << " microseconds\n";
    }
    return 0;
}