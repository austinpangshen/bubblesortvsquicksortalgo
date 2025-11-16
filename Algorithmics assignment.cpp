#include <iostream>
#include <chrono>
using namespace std;

//simple bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {            
        for (int j = 0; j < n - i - 1; j++) {    
            if (arr[j] > arr[j + 1]) {           
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//quick sort
int partitionAscending(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSortAscending(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionAscending(arr, low, high);
        quickSortAscending(arr, low, pi - 1);
        quickSortAscending(arr, pi + 1, high);
    }
}


//print Array function
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n = 1000;

    // Arrays
    int ascArrQS[1000], descArrQS[1000];
    int ascArrBS[1000], descArrBS[1000];

    // Fill arrays
    for (int i = 0; i < n; i++) {
        ascArrQS[i] = ascArrBS[i] = i + 1;      // 1, 2, 3, ...
        descArrQS[i] = descArrBS[i] = n - i;    // 10, 9, 8, ...
    }

    int choice;

    cout << "===== Sorting Menu =====\n";
    cout << "1. Quick Sort array Worst case (Input array in ascending order)\n";
    cout << "2. Quick Sort array Best case (Input array in descending order)\n";
    cout << "3. Bubble Sort array (Input array in ascending order)\n";
    cout << "4. Bubble Sort array (Input array in descending order)\n";
    cout << "Enter choice: ";
    cin >> choice;

    std::chrono::high_resolution_clock::time_point start, end;
    std::chrono::microseconds duration(0);

    switch (choice) {

        // QUICK SORT on ascending array
        case 1:
            cout << "\nOriginal ascending array:\n";
            printArray(ascArrQS, n);

            start = chrono::high_resolution_clock::now();
            quickSortAscending(ascArrQS, 0, n - 1);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Quick Sort:\n";
            printArray(ascArrQS, n);
            break;

        // QUICK SORT on descending array
        case 2:
            cout << "\nOriginal descending array:\n";
            printArray(descArrQS, n);

            start = chrono::high_resolution_clock::now();
            quickSortAscending(descArrQS, 0, n - 1);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Quick Sort (converted to ASC):\n";
            printArray(descArrQS, n);
            break;

        // BUBBLE SORT on ascending array
        case 3:
            cout << "\nOriginal ascending array:\n";
            printArray(ascArrBS, n);

            start = chrono::high_resolution_clock::now();
            bubbleSort(ascArrBS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Bubble Sort:\n";
            printArray(ascArrBS, n);
            break;

        // BUBBLE SORT on descending array
        case 4:
            cout << "\nOriginal descending array:\n";
            printArray(descArrBS, n);

            start = chrono::high_resolution_clock::now();
            bubbleSort(descArrBS, n);
            end = chrono::high_resolution_clock::now();

            cout << "\nAfter Bubble Sort (converted to ASC):\n";
            printArray(descArrBS, n);
            break;

        default:
            cout << "Invalid choice.\n";
            return 0;
    }

    // Compute duration only if start/end were set
    if (end > start) {
        duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "\nTime taken (sorting only): " << duration.count() << " microseconds\n";
    } else {
        cout << "\nTiming not recorded.\n";
    }

    return 0;
}



