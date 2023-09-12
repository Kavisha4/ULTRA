#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>  // Include for time function
#include <cstdlib>  // Include for rand function
#include "../Algorithms/Dijkstra/Dijkstra.h"  // Include the header for Dijkstra's algorithm

Graph initializeGraph(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        exit(1);
    }

    int numVertices, numEdges;
    std::string line;

    // ... (your code to read graph data)

    file.close();

    // Create and return the graph object
    return Graph(/* pass your graph data here */);
}


int main() {
    Graph graph = initializeGraph("USA-road-d.FLA.gr");

    // Initialize the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create a vector to store source-destination pairs
    std::vector<std::pair<int, int>> sourceDestPairs;

    for (int i = 0; i < 200; i++) {
        int source = rand() % graph.numVertices();
        int destination = rand() % graph.numVertices();
        sourceDestPairs.push_back({source, destination});
    }

    for (int i = 0; i < 200; i++) {
        int source = sourceDestPairs[i].first;
        int destination = sourceDestPairs[i].second;

        // Create a Dijkstra object to run it
        Dijkstra<Graph> dijkstra(graph);

        // Measure the runtime
        clock_t start_time = clock();
        dijkstra.run(source, destination);
        clock_t end_time = clock();
        double runtime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        // Output the runtime
        std::cout << "Total runtime in seconds for pair " << i + 1 << ": " << runtime << std::endl;
    }

    return 0;
}
