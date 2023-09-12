//Things to keep in mind
//I modified the exisiting Dijsktras to increase the time
// To implement the A* we need to use an heuristic


//1 Part is to modify exisitng dijkstras
// i did this by


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

// try to modify Dijkstra's algorithm to find the shortest path
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


// This is 2nd implementation of a * the heurisitic used is EUCLIDEAN DISTANCE
//usesa priority queue to store nodes based on their estimated total cost,
// which is the sum of the actual distance from the source, the heuristic value, and the edge weight

//

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

// Heuristic function for A* algorithm (Euclidean distance between coordinates)
double heuristic(const vector<pair<double, double>>& coordinates, int u, int v) {
    double x1 = coordinates[u].first;
    double y1 = coordinates[u].second;
    double x2 = coordinates[v].first;
    double y2 = coordinates[v].second;
// normal distance
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    return distance;
}

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

//A* algorithm to find the shortest path
vector<int> astar(const vector<vector<Edge>>& graph, int source, int destination) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    dist[source] = 0;
// used priortiy queue as it is better than set as th values are coming in asceding order, so make a min heap

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        double d = pq.top().first;
        pq.pop();

        if (u == destination) {
            // if it reaches the destination, i want it to terminate early
            break;
        }

        if (d > dist[u]) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.v;
            int w = edge.w;
            double heuristic_cost = heuristic(v, destination);
            if (dist[u] + w + heuristic_cost < dist[v]) {
                dist[v] = dist[u] + w + heuristic_cost;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // tryint to reconstruct the path from source to destination not sure where to use
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = prev[current];
    }
    reverse(path.begin(), path.end());

    return path;
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

    // calculate the total runtime for all 200 pairs
    clock_t start = clock();
    for (const pair<int, int>& pair : randomPairs) {
        vector<int> shortestPath = astar(graph, pair.first, pair.second);
    }
    clock_t end = clock();

    // Print the total runtime in seconds
    double totalRuntime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Total runtime in seconds for 200 random A* searches: " << totalRuntime << endl;

    return 0;
}