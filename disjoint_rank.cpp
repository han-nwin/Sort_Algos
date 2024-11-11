#include <iostream>
#include <vector>

class DisjointSet {
public:
  DisjointSet(int n) {
    parent.resize(n, -1);  // Initialize each element as its own root with rank 0 (-1)
  }

  // Find with path compression
  int find(int x) {
    if (parent[x] < 0) {  // If x is a root (negative rank)
      return x;
    }
    parent[x] = find(parent[x]);  // Path compression
    return parent[x];
  }

  // Union by rank using a single array
  void unionByRank(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
      int rankX = -parent[rootX];  // Get rank by negating the value
      int rankY = -parent[rootY];

      if (rankX > rankY) {
        parent[rootY] = rootX;  // rootY becomes child of rootX
                                // Rank x doesn't change
      } else if (rankX < rankY) {
        parent[rootX] = rootY;  // rootX becomes child of rootY
                                // Rank y doesn't change
      } else {
        parent[rootY] = rootX;   // If ranks are equal, choose one as root
        parent[rootX]--;     // Increase rank of rootX by making it more negative
      }
    }
  }

  // Utility function to print the parent array for debugging
  void print() {
    std::cout << "Element: ";
    for (int i = 0; i < parent.size(); ++i) std::cout << i << " ";
    std::cout << "\nParent/Rank: ";
    for (int i = 0; i < parent.size(); ++i) std::cout << parent[i] << " ";
    std::cout << std::endl;
  }

private:
  std::vector<int> parent;  // Stores both parent links and negative ranks
};

int main() {
  DisjointSet ds(5);  // Create 5 disjoint sets

  // Union operations
  ds.unionByRank(0, 1);
  ds.unionByRank(1, 2);
  ds.unionByRank(3, 4);

  // Find operations with path compression
  std::cout << "Find(2): " << ds.find(2) << std::endl;
  std::cout << "Find(4): " << ds.find(4) << std::endl;

  // Print internal structure for debugging
  ds.print();

  return 0;
}
