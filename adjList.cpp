#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Edge {
    string dest;
    int weight;
};

class Graph {
private:
    unordered_map<string, vector<Edge>> adjList;

public:
    void addVertex(string v) {
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = vector<Edge>();
        }
    }

    void addEdge(string src, string dest, int weight) {
        addVertex(src);
        addVertex(dest);
        
        Edge e1 = {dest, weight};
        Edge e2 = {src, weight};
        
        adjList[src].push_back(e1);
        adjList[dest].push_back(e2);
    }

    const unordered_map<string, vector<Edge>>& getAdjList() const {
        return adjList;
    }   

    void printGraph() {
        for (auto it = adjList.begin(); it != adjList.end(); it++) {
            cout << it->first << " -> ";
            for (size_t i = 0; i < it->second.size(); i++) {
                cout << "[" << it->second[i].dest << " (" << it->second[i].weight << "ms)] ";
            }
            cout << endl;
        }
    }
};