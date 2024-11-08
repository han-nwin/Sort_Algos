
#include <iostream>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    // Initialize each element to be its own parent (singleton set)
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 1); // Initial rank (or height) is 1 for each element
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the root of the set containing element x
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by rank - merge sets containing elements x and y
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Attach the smaller rank tree under the larger rank tree
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX] += 1; // Increase rank if both trees have the same rank
            }
        }
    }

    // Display the parent array for debugging
    void displayParents() {
        std::cout << "Parent array: ";
        for (int i = 0; i < static_cast<int>(parent.size()); i++) {
            std::cout << parent[i] << " ";
        }
        std::cout << std::endl;
    }
    void displayRank() {
        std::cout << "Rank array: ";
        for (int i = 0; i < static_cast<int>(rank.size()); i++) {
            std::cout << rank[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int n = 10; // Create a disjoint set with 10 elements (0 to 9)
    DisjointSet ds(n);

    // Perform some union operations
    ds.unionSets(0, 1);
    ds.unionSets(2, 3);
    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(8, 9);
    ds.unionSets(0, 2);
    ds.unionSets(4, 6);
    ds.unionSets(0, 4);

    // Display the parent array to see the structure
    ds.displayParents();
    ds.displayRank();

    // Find operation with path compression
    std::cout << "Find(9): " << ds.find(9) << std::endl;
    std::cout << "Find(3): " << ds.find(3) << std::endl;

    return 0;
}
