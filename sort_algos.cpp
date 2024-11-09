#include <iostream>
#include <ostream>
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
   for (size_t j = i - 1 ; static_cast<int>(j) >= 0; j--) {
     if (temp > arr[j]) {
       break;
     }
     std::swap(arr[j], arr[j+1]);
   }
 } 
}




int main() {
  std::vector<int> arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "ORIGINAL ARRAY" << std::endl;
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;

  std::cout << "BubbleSort" << std::endl;
  bubbleSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;
  

  arr = { 42, 17, 3, 88, 56, 23, 94, 12, 51, 78, 6, 33, 59, 71, 20, 15, 65, 87, 29, 9, 100, 46, 27, 11, 5};
  std::cout << "Insertion Sort" << std::endl;
  insertionSort(arr);
  for (auto & element : arr) {
    std::cout << element << ", ";
  }
  std::cout << std::endl;






  return 0;
}
