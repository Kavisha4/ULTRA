// #include <iostream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include "/Commands/BenchmarkMultimodal.h"

// void initializeGraph(const std::string& filePath) {
//     std::ifstream file(filePath);

//     if (!file.is_open()) {
//         std::cerr << "Error: Unable to open file " << filePath << std::endl;
//         exit(1);
//     }

//     int numVertices, numEdges;
//     std::string line;

//     // // Read lines until I need to find the problem line (p sp n m) given in the pdf
//     // while (getline(file, line)) {
//     //     if (line[0] == 'p') {
//     //         sscanf(line.c_str(), "%d %d", &numVertices, &numEdges);
//     //         break;
//     //     }
//     // }

//     // graph(numVertices);

//     while (getline(file, line)) {
//         if (line[0] == 'a') {
//             int u, v, weight;
//             sscanf(line.c_str(), "a %d %d %d", &u, &v, &weight);

//             // Add the edge (u, v) with weight to the graph
//             // into graph data structure
//             graph.addEdge(u, v, weight);
//         }
//     }

//     file.close();

//     return graph;
// }

// int main()
// {
//         graph = initializeGraph("USA-road-d.FLA.gr");

//     //  to take 200 random source-destination pairs
//     vector<pair<int, int>> sourceAndDestPairs;
//     srand(time(nullptr)); // Seed  random number generator

//     for (int i = 0; i < 200; i++) {
//         int source = rand() % graph.numVertices(); //source
//         int destination = rand() % graph.numVertices(); // dest
//         sourceDestPairs.push_back({source, destination});
//     }

//     //  for each source-destination pair
//     for (int i = 0; i < 200; i++) {
//         int source = sourceDestPairs[i].first;
//         int destination = sourceDestPairs[i].second;

//         // Create a dij object to run it
//         Dijkstra<Graph> dijkstra(graph);
//         dijkstra.run(source, destination);

//         // runtime for this pair
//         cout << "Total runtime in seconds for pair " << i + 1 << ": " << dijkstra.getRuntimeInSeconds() << endl;
//     }

//     return 0;
// }
// }

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "../Algorithms/Dijkstra/Dijkstra.h"
#include<utility>


// Define your Graph class (assuming you have one)
class Graph {
public:

std::vector<std::pair<int, int>> adj[200];

void addEdge(int u, int v, int weight) {
    // Add an edge from u to v with the given weight
    adj[u].emplace_back(v, weight);
}

    int numVertices() {
        // Implement your logic to return the number of vertices
        return 0;
    }
};

// Modify initializeGraph to return the created Graph object
Graph initializeGraph(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        exit(1);
    }

    int numVertices, numEdges;
    std::string line;

    // Read lines until you find the problem line (p sp n m)
    while (getline(file, line)) {
        if (line[0] == 'p') {
            sscanf(line.c_str(), "p sp %d %d", &numVertices, &numEdges);
            break;
        }
    }

    Graph graph;

    while (getline(file, line)) {
        if (line[0] == 'a') {
            int u, v, weight;
            sscanf(line.c_str(), "a %d %d %d", &u, &v, &weight);

            // Add the edge (u, v) with weight to the graph
            graph.addEdge(u, v, weight);
        }
    }

    file.close();

    return graph;
}

int main() {
    Graph graph = initializeGraph("TestCase1-Sample");

    // To take 200 random source-destination pairs
    std::vector<std::pair<int, int>> sourceDestPairs;
    srand(time(nullptr)); // Seed random number generator

    for (int i = 0; i < 200; i++) {
        int source = rand() % graph.numVertices(); // Source
        int destination = rand() % graph.numVertices(); // Destination
        sourceDestPairs.push_back({source, destination});
    }

    // For each source-destination pair
    for (int i = 0; i < 200; i++) {
        int source = sourceDestPairs[i].first;
        int destination = sourceDestPairs[i].second;

        // Create a Dijkstra object to run it
        // You may need to update the Dijkstra class instantiation based on your implementation
        // Dijkstra<Graph> dijkstra(graph);

        // Measure the runtime
        clock_t start_time = clock();
        // dijkstra.run(source, destination);
        clock_t end_time = clock();
        double runtime = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        // Output the runtime
        std::cout << "Total runtime in seconds for pair " << i + 1 << ": " << runtime << std::endl;
    }

    return 0;
}
