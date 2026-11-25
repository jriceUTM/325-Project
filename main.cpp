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
    Graph graph;
    graph.addEdge("R1", "R2", 4);
    graph.addEdge("R1", "R3", 2);
    graph.addEdge("R2", "R3", 1);
    graph.addEdge("R2", "R4", 5);
    graph.addEdge("R3", "R4", 8);
    graph.addEdge("R3", "R5", 10);
    graph.addEdge("R4", "R5", 2);

    int choice = 0;

    while (true) {
        cout << endl;
        cout << "Network Routing Simulator" << endl;
        cout << "1. View Network" << endl;
        cout << "2. Send Packet" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice. Enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            graph.printGraph();
        }
        else if (choice == 2) {
            string source;
            string destination;

            cout << "Source router: ";
            cin >> source;
            cout << "Destination router: ";
            cin >> destination;

            const auto& adjList = graph.getAdjList();
            if (!adjList.count(source) || !adjList.count(destination)) {
                cout << "Invalid router. Use a router that exists in the network." << endl;
                continue;
            }

            vector<string> path = dijkstra(graph, source, destination);
            if (path.empty()) {
                cout << "No route found between those routers." << endl;
                continue;
            }

            cout << "Shortest path: ";
            for (size_t i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i + 1 < path.size()) {
                    cout << " -> ";
                }
            }
            cout << endl;

            int latency = 0;
            for (size_t i = 0; i + 1 < path.size(); i++) {
                for (const Edge& edge : adjList.at(path[i])) {
                    if (edge.dest == path[i + 1]) {
                        latency += edge.weight;
                        break;
                    }
                }
            }

            cout << "Total latency: " << latency << "ms" << endl;
        }
        else if (choice == 3) {
            cout << "Goodbye." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Enter 1, 2, or 3." << endl;
        }
    }

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
