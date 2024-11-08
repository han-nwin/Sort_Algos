
#include <iostream>
#include <vector>
#include <algorithm>

int getMax(const std::vector<int>& arr) {
    int maxVal = arr[0];
    for (int num : arr) {
        if (num > maxVal) {
            maxVal = num;
        }
    }
    return maxVal;
}

void countingSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n); // Output array to hold sorted values
    std::vector<int> count(10, 0); // Count array for each digit (0-9)

    // Count occurrences of each digit in the given exponent place
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Update count array to contain actual positions
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void radixSort(std::vector<int>& arr) {
    int maxVal = getMax(arr);

    // Perform counting sort for each digit position (1, 10, 100, etc.)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, exp);
        std::cout << "After sorting by " << exp << "s place: ";
        printArray(arr);
    }
}

int main() {
    std::vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    std::cout << "Original array:\n";
    printArray(arr);

    radixSort(arr);

    std::cout << "\nFinal sorted array:\n";
    printArray(arr);

    return 0;
}
