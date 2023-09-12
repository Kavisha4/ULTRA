#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "/Commands/BenchmarkMultimodal.h"

void initializeGraph(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        exit(1);
    }

    int numVertices, numEdges;
    std::string line;

    // // Read lines until I need to find the problem line (p sp n m) given in the pdf
    // while (getline(file, line)) {
    //     if (line[0] == 'p') {
    //         sscanf(line.c_str(), "%d %d", &numVertices, &numEdges);
    //         break;
    //     }
    // }

    // graph(numVertices);

    while (getline(file, line)) {
        if (line[0] == 'a') {
            int u, v, weight;
            sscanf(line.c_str(), "a %d %d %d", &u, &v, &weight);

            // Add the edge (u, v) with weight to the graph
            // into graph data structure
            graph.addEdge(u, v, weight);
        }
    }

    file.close();

    return graph;
}

int main()
{
        graph = initializeGraph("USA-road-d.FLA.gr");

    //  to take 200 random source-destination pairs
    vector<pair<int, int>> sourceAndDestPairs;
    srand(time(nullptr)); // Seed  random number generator

    for (int i = 0; i < 200; i++) {
        int source = rand() % graph.numVertices(); //source
        int destination = rand() % graph.numVertices(); // dest
        sourceDestPairs.push_back({source, destination});
    }

    //  for each source-destination pair
    for (int i = 0; i < 200; i++) {
        int source = sourceDestPairs[i].first;
        int destination = sourceDestPairs[i].second;

        // Create a dij object to run it
        Dijkstra<Graph> dijkstra(graph);
        dijkstra.run(source, destination);

        // runtime for this pair
        cout << "Total runtime in seconds for pair " << i + 1 << ": " << dijkstra.getRuntimeInSeconds() << endl;
    }

    return 0;
}
}