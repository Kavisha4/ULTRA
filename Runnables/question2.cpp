#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <climits>

using namespace std;

//  to represent an edge in the graph
struct Edge {
    int v;      // Destination vertex
    int w;      // Weight of the edge
};

// Function to read the .gr file and create a graph representation
vector<vector<Edge>> readGraph(const string& filename, int& n, int& m) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open the file " << filename << endl;
        exit(1);
    }

    char type;
    file >> type >> n >> m;

    vector<vector<Edge>> graph(n);

    while (!file.eof()) {
        char c;
        int u, v, w;
        file >> c;

        if (c == 'a') {
            file >> u >> v >> w;
            graph[u - 1].push_back({v - 1, w});
        }
    }

    file.close();
    return graph;
}

// Modified Dijkstra's algorithm to find the shortest path
vector<int> dijkstra(const vector<vector<Edge>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.v;
            int w = edge.w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int n, m;
vector<vector<Edge>> graph = readGraph(R"(C:\CiSTup\ULTRA\Runnables\USA-road-d.FLA.gr)", n, m);

    // Generate 200 random source-destination pairs
    srand(time(nullptr));
    vector<pair<int, int>> randomPairs;
    for (int i = 0; i < 200; ++i) {
        int source = rand() % n;
        int dest = rand() % n;
        randomPairs.push_back({source, dest});
    }

    // Calculate the total runtime for all 200 pairs
    clock_t start = clock();
    for (const pair<int, int>& pair : randomPairs) {
        vector<int> shortestPath = dijkstra(graph, pair.first);
    }
    clock_t end = clock();

    // Print the total runtime in seconds
    double totalRuntime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Total runtime in seconds for 200 random modified Dijkstra: " << totalRuntime << endl;

    return 0;
}
