#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <string>

// Define the Node structure to represent nodes in the grid
struct Node {
    int x, y;     // Coordinates
    int value;    // Weight or cost
    bool blocked; // Indicates if the node is blocked or not

    Node(int x, int y, int value, bool blocked = false) : x(x), y(y), value(value), blocked(blocked) {}
};

// Define a custom comparator for nodes in the priority queue
struct CompareNodes {
    bool operator()(const Node& a, const Node& b) const {
        return a.value > b.value;
    }
};

// Function to initialize the grid from a DIMACS-style file
bool initializeGridFromFile(const std::string& filename, std::vector<std::vector<Node>>& grid, Node& start, Node& goal) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char type;
        int x, y, value;

        if (!(iss >> type)) continue; // Skip empty lines

        if (type == 'c') continue; // Skip comment lines

        if (type == 'p') {
            // Parse problem line (p sp numNodes numEdges)
            std::string problemType;
            int numNodes, numEdges;
            if (!(iss >> problemType >> numNodes >> numEdges)) {
                std::cerr << "Error: Invalid problem line format." << std::endl;
                return false;
            }
            // Resize the grid based on the number of nodes (adjust as needed)
            grid.resize(numNodes, std::vector<Node>(numNodes, Node(0, 0, 0, false)));
        } else if (type == 'a') {
            // Parse edge descriptor (a u v w)
            if (!(iss >> x >> y >> value)) {
                std::cerr << "Error: Invalid edge descriptor format." << std::endl;
                return false;
            }
            // Set the weight in the grid (you can adjust this as needed)
            grid[x - 1][y - 1] = Node(x - 1, y - 1, value);
        }
    }

    // Set the start and goal nodes (you can adjust this as needed)
    start = grid[0][0];
    goal = grid[grid.size() - 1][grid[0].size() - 1];

    return true;
}

// A* search algorithm
int astarSearch(const std::vector<std::vector<Node>>& grid, const Node& start, const Node& goal) {
    const int numRows = grid.size();
    const int numCols = grid[0].size();

    // Create a 2D vector to store the cost-so-far
    std::vector<std::vector<int>> costSoFar(numRows, std::vector<int>(numCols, INT_MAX));

    // Create a priority queue for open nodes
    std::priority_queue<Node, std::vector<Node>, CompareNodes> openSet;

    // Initialize the starting node
    costSoFar[start.x][start.y] = 0;
    openSet.push(start);

    while (!openSet.empty()) {
        // Get the node with the lowest cost from the open set
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goal.x && current.y == goal.y) {
            // Reached the goal
            return costSoFar[goal.x][goal.y];
        }

        // Define possible neighbor directions (up, down, left, right)
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Check if the neighbor is within bounds
            if (newX >= 0 && newX < numRows && newY >= 0 && newY < numCols) {
                const Node& neighbor = grid[newX][newY];

                if (!neighbor.blocked) {
                    int newCost = costSoFar[current.x][current.y] + neighbor.value;

                    if (newCost < costSoFar[newX][newY]) {
                        costSoFar[newX][newY] = newCost;
                        openSet.push(Node(newX, newY, newCost));
                    }
                }
            }
        }
    }

    // If the goal is unreachable
    return -1;
}

int main() {
    // Define the filename for the DIMACS-style graph file
    std::string filename = "your_graph.gr";

    // Initialize the grid and start/goal nodes from the file
    std::vector<std::vector<Node>> grid;
    Node start, goal;

    if (!initializeGridFromFile(filename, grid, start, goal)) {
        return 1; // Exit with an error code
    }

    // Perform A* search
    int result = astarSearch(grid, start, goal);

    if (result != -1) {
        std::cout << "Shortest path cost: " << result << std::endl;
    } else {
        std::cout << "Goal is unreachable." << std::endl;
    }

    return 0;
}
