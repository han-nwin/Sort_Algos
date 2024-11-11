#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class DisjointSet {
public:
  explicit DisjointSet(int n) : parent(n, -1) {}

  // Find with path compression
  int find(int u) {
    if (parent[u] < 0) {
      return u;  // Root node
    }
    return parent[u] = find(parent[u]);  // Path compression
  }

  // Union by rank, storing -rank at the root
  bool unionSets(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV) {
      // Union by rank
      if (parent[rootU] < parent[rootV]) {
        parent[rootU] += parent[rootV];  // Increase rank
        parent[rootV] = rootU;
      } else {
        parent[rootV] += parent[rootU];  // Increase rank
        parent[rootU] = rootV;
      }
      return true;  // Successfully merged
    }
    return false;  // Would form a cycle
  }

private:
  std::vector<int> parent;
};

// Structure to represent a wall between two cells
struct Wall {
  int cell1, cell2;
  char direction;
};

// Maze cell structure with walls
struct Cell {
  bool top = true, right = true;  // Initialize walls as present
};

class Maze {
public:
  Maze(int width, int height) : width(width), height(height) {
    maze.resize(height, std::vector<Cell>(width));
  }

  void generateMaze() {
    DisjointSet ds(width * height);
    std::vector<Wall> walls = generateWalls();
    std::shuffle(walls.begin(), walls.end(), std::mt19937{std::random_device{}()});

    for (const auto& wall : walls) {
      if (ds.unionSets(wall.cell1, wall.cell2)) {
        removeWall(wall);
      }
    }
  }

  void printMaze() const {
    for (int y = 0; y < height; ++y) {
      // Top walls
      for (int x = 0; x < width; ++x) {
        std::cout << (maze[y][x].top ? " _" : "  ");
      }
      std::cout << "\n";
      // Left walls and spaces
      for (int x = 0; x < width; ++x) {
        std::cout << (x == 0 || maze[y][x - 1].right ? "|" : " ");
        std::cout << (maze[y][x].top ? " " : "_");
      }
      std::cout << "|\n";  // Right boundary
    }
  }

private:
  struct Cell {
    bool top = true;
    bool right = true;
  };

  int width, height;
  std::vector<std::vector<Cell>> maze;

  std::vector<Wall> generateWalls() {
    std::vector<Wall> walls;
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        int cell = y * width + x;
        if (x < width - 1) {
          walls.push_back({cell, cell + 1, 'R'});  // Right wall
        }
        if (y < height - 1) {
          walls.push_back({cell, cell + width, 'B'});  // Bottom wall
        }
      }
    }
    return walls;
  }

  void removeWall(const Wall& wall) {
    int x1 = wall.cell1 % width, y1 = wall.cell1 / width;
    int x2 = wall.cell2 % width, y2 = wall.cell2 / width;

    if (wall.direction == 'R') {
      maze[y1][x1].right = false;
    } else if (wall.direction == 'B') {
      maze[y1][x1].top = false;
    }
  }
};

int main() {
  int width = 5, height = 5;
  Maze maze(width, height);
  maze.generateMaze();
  maze.printMaze();
  return 0;
}
