#include <iostream>
#include <cstdio>

void merge(long long *arr, int left, int right, int *counter, long long *brr) {
    int k = left;
    int mid = (left + right) / 2;
    int i=left, j=mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] > arr[j]) {
            brr[k] = arr[j];
            k++, j++;
            (*counter) += mid - i + 1;
        } else {
            brr[k] = arr[i];
            k++, i++;
        }
    }
    for (i; i< = mid; ++i) {
        brr[k] = arr[i];
        k++;
    }
    for (j; j <= right; ++j) {
        brr[k] = arr[j];
        k++;
    }
    for (i = left; i <= right; ++i) {
        arr[i] = brr[i];
    }
}

void mergesort(long long *arr, int left, int right, int *counter, long long *brr) {
    if (left >= right) { return; }
    int mid = (left + right) / 2;
    mergesort(arr, left, mid, counter, brr);
    mergesort(arr, mid+1, right, counter, brr);
    merge(arr, left, right, counter, brr);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    int n, counter=0;
    std::cin >> n;
    long long arr[n], brr[n];
    for(int i=0; i<n; ++i) {
        std::cin >> arr[i];
    }
    mergesort(arr, 0, n, &counter, brr);
    std::cout << counter;
}#include <iostream>
#include <cstdio>

void merge(long long *arr, int left, int right, int *counter, long long *brr) {
    int k = left;
    int mid = (left + right) / 2;
    int i=left, j=mid + 1;
    while (i <= mid && j <= right) {
        if (arr[i] > arr[j]) {
            brr[k] = arr[j];
            k++, j++;
            (*counter) += mid - i + 1;
        } else {
            brr[k] = arr[i];
            k++, i++;
        }
    }
    for (i; i< = mid; ++i) {
        brr[k] = arr[i];
        k++;
    }
    for (j; j <= right; ++j) {
        brr[k] = arr[j];
        k++;
    }
    for (i = left; i <= right; ++i) {
        arr[i] = brr[i];
    }
}

void mergesort(long long *arr, int left, int right, int *counter, long long *brr) {
    if (left >= right) { return; }
    int mid = (left + right) / 2;
    mergesort(arr, left, mid, counter, brr);
    mergesort(arr, mid+1, right, counter, brr);
    merge(arr, left, right, counter, brr);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    int n, counter=0;
    std::cin >> n;
    long long arr[n], brr[n];
    for(int i=0; i<n; ++i) {
        std::cin >> arr[i];
    }
    mergesort(arr, 0, n, &counter, brr);
    std::cout << counter;
}
