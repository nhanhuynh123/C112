#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <algorithm>

struct Edge {
    std::string u, v;
    int weight;
};

int findMinVertex(std::vector<int>& distances, std::vector<bool>& visited) {
    int minDistance = std::numeric_limits<int>::max();
    int minVertex = -1;
    for (size_t i = 0; i < distances.size(); ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void dijkstra(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph, const std::string& start, std::unordered_map<std::string, int>& distances) {
    std::vector<std::string> vertices;
    for (const auto& kv : graph) {
        vertices.push_back(kv.first);
    }

    std::unordered_map<std::string, int> vertexToIndex;
    for (size_t i = 0; i < vertices.size(); ++i) {
        vertexToIndex[vertices[i]] = i;
    }

    std::vector<int> dist(vertices.size(), std::numeric_limits<int>::max());
    std::vector<bool> visited(vertices.size(), false);

    dist[vertexToIndex[start]] = 0;

    for (size_t i = 0; i < vertices.size(); ++i) {
        int minVertex = findMinVertex(dist, visited);
        visited[minVertex] = true;

        for (const auto& neighbor : graph.at(vertices[minVertex])) {
            int edgeWeight = neighbor.second;
            int newDist = dist[minVertex] + edgeWeight;
            if (newDist < dist[vertexToIndex[neighbor.first]]) {
                dist[vertexToIndex[neighbor.first]] = newDist;
            }
        }
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        distances[vertices[i]] = dist[i];
    }
}

void tsp(const std::unordered_map<std::string, std::unordered_map<std::string, int>>& graph, const std::string& start) {
    std::vector<std::string> vertices;
    for (const auto& kv : graph) {
        if (kv.first != start) {
            vertices.push_back(kv.first);
        }
    }

    std::vector<std::string> bestPath;
    int bestCost = std::numeric_limits<int>::max();

    std::sort(vertices.begin(), vertices.end());

    do {
        int currentCost = 0;
        std::string currentVertex = start;

        for (const auto& vertex : vertices) {
            currentCost += graph.at(currentVertex).at(vertex);
            currentVertex = vertex;
        }

        currentCost += graph.at(currentVertex).at(start);

        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = vertices;
        }
    } while (std::next_permutation(vertices.begin(), vertices.end()));

    std::cout << "Shortest path cost: " << bestCost << std::endl;
    std::cout << "Path: " << start << " ";
    for (const auto& vertex : bestPath) {
        std::cout << vertex << " ";
    }
    std::cout << start << std::endl;
}

int main() {
    int e;
    std::string start;
    std::cin >> e >> start;

    std::unordered_map<std::string, std::unordered_map<std::string, int>> graph;

    for (int i = 0; i < e; ++i) {
        std::string u, v;
        int w;
        std::cin >> u >> v >> w;
        graph[u][v] = w;
    }

    tsp(graph, start);

    return 0;
}
