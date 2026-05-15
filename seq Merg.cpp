#include <iostream>
#include <vector>

using namespace std;

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

void mergeSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);

        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
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

    mergeSort(arr, 0, n - 1);

    cout << "\nSorted Array:\n";

    for (int num : arr) {

        cout << num << " ";
    }

    return 0;
}