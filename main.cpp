#include <queue>
#include <unordered_map>
#include <limits>
#include <functional>
#include <utility>
#include "adjList.cpp"

using namespace std;

vector<string> dijkstra(
    const Graph& graph,
    const string& source,
    const string& destination
);



int main()
{


    return 0;
}




vector<string> dijkstra(const Graph& graph,
    const string& source,
    const string& destination)
{
    const auto& adjList = graph.getAdjList();

    // Check if both routers exist
    if (!adjList.count(source) || !adjList.count(destination)) {
        return {};
    }

    unordered_map<string, int> distances;
    unordered_map<string, string> previous;

    // Min-heap: (distance, router)
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string current = pq.top().second;
        pq.pop();

        // Skip outdated distances
        if (currentDistance > distances[current]) {
            continue;
        }

        if (current == destination) {
            break;
        }

         // Check all neighbors
        for (const Edge& edge : adjList.at(current)) {
            string neighbor = edge.dest;
            int newDistance = currentDistance + edge.weight;

            // Update if a shorter path is found
            if (!distances.count(neighbor) ||
                newDistance < distances[neighbor]) {

                distances[neighbor] = newDistance;
                previous[neighbor] = current;
                pq.push({newDistance, neighbor});
            }
        }
    }

    // No path found
    if (!distances.count(destination)) {
        return {};
    }

    // Build the shortest path
    vector<string> path;
    string current = destination;

    while (current != source) {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(source);
    reverse(path.begin(), path.end());

    return path;
}

