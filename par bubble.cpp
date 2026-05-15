#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

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

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {

        cin >> arr[i];
    }

    parallelBubbleSort(arr);

    cout << "\nSorted Array:\n";

    for (int num : arr) {

        cout << num << " ";
    }

    return 0;
}