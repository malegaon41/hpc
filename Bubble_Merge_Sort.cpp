
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

// ---------------- Bubble Sort ----------------

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ---------------- Merge Sort ----------------

// Merge Function
void merge(vector<int>& arr, int low, int mid, int high) {

    vector<int> temp;

    int i = low;
    int j = mid + 1;

    while (i <= mid && j <= high) {

        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);
        }
    }

    while (i <= mid)
        temp.push_back(arr[i++]);

    while (j <= high)
        temp.push_back(arr[j++]);

    for (int k = low; k <= high; k++) {
        arr[k] = temp[k - low];
    }
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        sequentialMergeSort(arr, low, mid);

        sequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

// Print Array
void printArray(vector<int>& arr) {

    for (int num : arr) {
        cout << num << " ";
    }

    cout << endl;
}

// Main Function
int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> bubbleSeq = arr;
    vector<int> bubblePar = arr;
    vector<int> mergeSeq = arr;
    vector<int> mergePar = arr;

    // Sequential Bubble Sort
    auto start1 = high_resolution_clock::now();

    sequentialBubbleSort(bubbleSeq);

    auto end1 = high_resolution_clock::now();

    duration<double> time1 = end1 - start1;

    cout << "\nSequential Bubble Sort:\n";
    printArray(bubbleSeq);

    cout << "Time: " << time1.count() << " seconds\n";

    // Parallel Bubble Sort
    auto start2 = high_resolution_clock::now();

    parallelBubbleSort(bubblePar);

    auto end2 = high_resolution_clock::now();

    duration<double> time2 = end2 - start2;

    cout << "\nParallel Bubble Sort:\n";
    printArray(bubblePar);

    cout << "Time: " << time2.count() << " seconds\n";

    // Sequential Merge Sort
    auto start3 = high_resolution_clock::now();

    sequentialMergeSort(mergeSeq, 0, n - 1);

    auto end3 = high_resolution_clock::now();

    duration<double> time3 = end3 - start3;

    cout << "\nSequential Merge Sort:\n";
    printArray(mergeSeq);

    cout << "Time: " << time3.count() << " seconds\n";

    // Parallel Merge Sort
    auto start4 = high_resolution_clock::now();

    parallelMergeSort(mergePar, 0, n - 1);

    auto end4 = high_resolution_clock::now();

    duration<double> time4 = end4 - start4;

    cout << "\nParallel Merge Sort:\n";
    printArray(mergePar);

    cout << "Time: " << time4.count() << " seconds\n";

    return 0;
}   

/*Sample Input
6
64 34 25 12 22 11*/