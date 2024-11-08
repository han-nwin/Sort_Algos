#include <iostream>
#include <vector>
#include <iomanip>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> height;

public:
    // Initialize each element as its own root with height 0
    DisjointSet(int n) {
        parent.resize(n);
        height.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union by height
    void unionByHeight(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (height[rootX] < height[rootY]) {
                parent[rootX] = rootY;
            } else if (height[rootX] > height[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                height[rootX]++;
            }
        }
    }

    // Print the current tree structure and array
    void printSets() {
        std::cout << "Parent array: ";
        for (int i = 0; i < parent.size(); ++i) {
            std::cout << std::setw(2) << parent[i] << " ";
        }
        std::cout << "\n";


        std::cout << "Height array: ";
        for (int i = 0; i < height.size(); ++i) {
            std::cout << std::setw(2) << height[i] << " ";
        }
        std::cout << "\n";

        std::cout << "Tree structure:\n";
        for (int i = 0; i < parent.size(); ++i) {
            std::cout << i << " -> " << parent[i] << "\n";
        }
        std::cout << "\n";
    }

    // Perform union operations and print each stage
    void processUnions(const std::vector<std::pair<int, int>>& operations) {
        for (const auto& op : operations) {
            std::cout << "Union(" << op.first << ", " << op.second << "):\n";
            unionByHeight(op.first, op.second);
            printSets();
        }
    }

    // Perform find with path compression on the specified node and print result
    void findWithCompression(int x) {
        std::cout << "Find(" << x << ") with path compression:\n";
        int root = find(x);
        printSets();
        std::cout << "Root of " << x << " is " << root << "\n\n";
    }
};

int main() {
    int n = 17;
    DisjointSet ds(n);

    std::vector<std::pair<int, int>> unionOps = {
        {1, 2}, {3, 4}, {3, 5}, {1, 7}, {3, 6}, {8, 9}, {1, 8}, {3, 10},
        {3, 11}, {3, 12}, {3, 13}, {14, 15}, {16, 0}, {14, 16}, {1, 3}, {1, 14}
    };

    // Perform unions and display the state after each operation
    ds.processUnions(unionOps);

    // Perform find with path compression on the deepest node of each tree
    ds.findWithCompression(13); // Example node
    ds.findWithCompression(16); // Example node

    return 0;
}
