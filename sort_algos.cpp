#include <algorithm>
#include <iostream>
#include <ostream>
#include <queue>
#include <vector>


void bubbleSort(std::vector<int> & arr) {
  int flag = 0;

  for (size_t i = 1; i < arr.size() - 1; i++) {
    for (size_t j = 0; j < (arr.size() - i); j++) {
      if (arr[j] > arr[j+1]) {
        std::swap(arr[j], arr[j+1]);
        flag = 1;
      }
    }
    if (flag == 0) {
      break;
    }
  }

}

void insertionSort(std::vector<int> & arr) {
 for (size_t i = 1; i < arr.size(); i++) {
   int temp = arr[i];
   int j = static_cast<int>(i) -1;

   while(temp < arr[j] && j >=0) {
     arr[j+1] = arr[j];
     j -= 1;
   }
   arr[j+1] = temp;

 } 
}

void shellSort (std::vector<int> & arr) {

  int n = static_cast<int>(arr.size());

  for (int gap = n/2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {

      int temp = arr[i];
      int j = i;

      while (j >= gap && temp < arr[j-gap]) {
        arr[j] = arr[j-gap];
        j -= gap;
      }

      arr[j] = temp;

    }

  }

}

void heapSort (std::vector<int> & arr) {

  std::make_heap(arr.begin(), arr.end());//build a max heap 
  
  for (size_t i = 0; i < arr.size(); i++) {
    std::pop_heap(arr.begin(), arr.end()-i); //move top element to the end and build smaller heap every interation
  }
  
  
}

std::vector<int> merge(std::vector<int> & left, std::vector<int> & right) {
  size_t i = 0;
  size_t j = 0;
  std::vector<int> newArr;
  while (i < left.size() && j < right.size()) {
    if (left[i] <= right[j]) {
      newArr.push_back(left[i]);
      i++;
    } else {
      newArr.push_back(right[j]);
      j++;
    }
  }

  while (i < left.size()) {
    newArr.push_back(left[i]);
    i++;
  }

  while (j < right.size()) {
    newArr.push_back(right[j]);
    j++;
  }
  return newArr;
}

void mergeSort(std::vector<int> & arr) {

  if (arr.size() <= 1) return;

  size_t n = arr.size()/2;

  std::vector<int> left(arr.begin(), arr.begin() + n);
  std::vector<int> right(arr.begin() + n, arr.end());

  mergeSort(left);
  mergeSort(right);

  arr = merge(left, right);

}

int medianThree (std::vector<int> & arr, int left, int right) {
  int mid = (left + right)/2;
  
  if (arr[mid] < arr[left]) {
    std::swap(arr[mid], arr[left]);
  }
  if (arr[right] < arr[left]) {
    std::swap(arr[right], arr[left]);
  }
  if (arr[right] < arr[mid]) {
    std::swap(arr[right], arr[mid]);
  }

  //Place the pivot at the position before the end of the array
  std::swap(arr[mid], arr[right-1]);

  return arr[right-1];

}

// QuickSort function with small subarray handling
void insertionSort2(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int temp = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > temp) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = temp;
  }
}

void quickSort (std::vector<int> & arr, int left, int right) {
  if ((left+10) <= right) {
    int pivot = medianThree(arr, left, right);
    int i = left;
    int j = right-1;

    while (1) {
      while (arr[++i] < pivot) {}; //move left cursor
      while (arr[--j] > pivot) {}; //move right cursor

      if (i < j) {
        std::swap(arr[i], arr[j]);
      } else break;
    }

    std::swap(arr[i], arr[right-1]); // Move the pivot to middle
                                     //
    quickSort(arr, left, i-1);//Sort small elements
    quickSort(arr, i+1, right);//Sort large element
  } else {
    insertionSort2(arr, left, right);

  }
}


void bucketSort (std::vector<int> & arr) {
  std::vector<int> arrB(200,0);//only sort list of integer < (M = 200)
  for (int & element : arr) {
    arrB[element] += 1;
  }
  std::vector<int> newArr;
  for (size_t i = 0; i < arrB.size(); i++) {
    for (int j = 0; j < arrB[i]; j++) {
      newArr.push_back(i);
    }
  }
  arr = newArr;
}

void radixSort(std::vector<int>& arr, int power, int base) {
    // Create buckets (queues) for each digit (0 to base - 1)
    std::vector<std::queue<int>> arrB(base);

    // Iterate over each digit position, from least significant to most significant
    int divisor = 1;
    for (int i = 0; i <= power; i++) {
        // Distribute numbers into the appropriate bucket based on the current digit
        for (size_t j = 0; j < arr.size(); j++) {
            int digit = (arr[j] / divisor) % base;
            arrB[digit].push(arr[j]);
        }

        // Collect numbers back from the buckets into arr
        int index = 0;
        for (int k = 0; k < base; k++) {
            while (!arrB[k].empty()) {
                arr[index++] = arrB[k].front();
                arrB[k].pop();
            }
        }

        // Move to the next digit position
        divisor *= base;
    }
}


int main() {
  std::vector<int> arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "ORIGINAL ARRAY" << std::endl;
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;

  std::cout << "\nBubbleSort N^2" << std::endl;
  bubbleSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;
  

  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nInsertion Sort N^2" << std::endl;
  insertionSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;


  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nShell Sort Nlog^2N" << std::endl;
  shellSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;


  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nHeap Sort 24.5NlogN" << std::endl;
  heapSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;


  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nMerger Sort 24.5NlogN" << std::endl;
  mergeSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;



  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nQuick Sort N^2-wc NlogN-ac" << std::endl;
  quickSort(arr, 0, arr.size()-1);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;


  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 51, 6, 33, 59, 71, 20, 6, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nBucket Sort O(M+N)" << std::endl;
  bucketSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;


  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 51, 6, 33, 59, 71, 20, 6, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "\nRadix Sort O(p(N+b))" << std::endl;
  radixSort(arr, 3, 10);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;

  return 0;
}
