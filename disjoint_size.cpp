
#include <iostream>
#include <vector>

class DisjointSet {
public:
  DisjointSet(int n) {
    parent.resize(n, -1);  // Each element is its own root, with size -1
  }

  // Find with path compression
  int find(int x) {
    if (parent[x] < 0) {  // If x is a root
      return x;
    }
    return parent[x] = find(parent[x]);  // Path compression
    //return parent[x];
  }

  // Union by size
  void unionBySize(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
      if (parent[rootX] < parent[rootY]) {  // rootX has a larger size
        parent[rootX] += parent[rootY];  // Add sizes
        parent[rootY] = rootX;       // rootY becomes child of rootX
      } else {
        parent[rootY] += parent[rootX];  // Add sizes
        parent[rootX] = rootY;       // rootX becomes child of rootY
      }
    }
  }

  // Utility function to print parent array (for testing/debugging)
  void print() {
    std::cout << "Element: ";
    for (int i = 0; i < parent.size(); ++i) std::cout << i << " ";
    std::cout << "\nParent/Size: ";
    for (int i = 0; i < parent.size(); ++i) std::cout << parent[i] << " ";
    std::cout << std::endl;
  }

private:
  std::vector<int> parent;  // Stores parent and size (negative if root)
};

int main() {
  DisjointSet ds(5);  // Create 5 disjoint sets

  // Union operations
  ds.unionBySize(0, 1);
  ds.unionBySize(1, 2);
  ds.unionBySize(3, 4);

  // Find operations with path compression
  std::cout << "Find(2): " << ds.find(2) << std::endl;
  std::cout << "Find(4): " << ds.find(4) << std::endl;

  // Print internal structure for debugging
  ds.print();

  return 0;
}
