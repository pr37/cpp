You are given a directed graph representing a network of routers. 
Each node represents a router, and each directed edge represents a connection between two routers.
 Write a C++ function that finds the shortest path between two routers using Dijkstra's algorithm.

 #include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct Node {
    int vertex;
    int distance;
    
    bool operator>(const Node &other) const {
        return distance > other.distance;
    }
};

class Graph {
public:
    int V; // Number of vertices (routers)
    vector<vector<Edge>> adjList;

    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    // Add directed edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
    }

    // Dijkstra's algorithm to find the shortest path from source to destination
    vector<int> dijkstra(int source) {
        vector<int> dist(V, INT_MAX); // Distance array
        priority_queue<Node, vector<Node>, greater<Node>> pq; // Min-heap to get the minimum distance node
        dist[source] = 0;
        
        pq.push({source, 0});

        while (!pq.empty()) {
            int u = pq.top().vertex;
            pq.pop();

            // Explore all neighbors of u
            for (const auto &edge : adjList[u]) {
                int v = edge.destination;
                int weight = edge.weight;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({v, dist[v]});
                }
            }
        }

        return dist;
    }

    // Function to print the shortest path from source to destination
    void printShortestPath(int source, int destination) {
        vector<int> dist = dijkstra(source);
        if (dist[destination] == INT_MAX) {
            cout << "No path from " << source << " to " << destination << endl;
        } else {
            cout << "The shortest path from router " << source << " to router " << destination
                 << " is " << dist[destination] << endl;
        }
    }
};

int main() {
    int V = 6; // Number of routers (vertices)
    Graph g(V);

    // Adding directed edges with weights (router1 -> router2, weight)
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 5);

    // Define source and destination routers
    int source = 0;
    int destination = 5;

    // Finding and printing the shortest path
    g.printShortestPath(source, destination); //The shortest path from router 0 to router 5 is 12

    return 0;
}


Graph Representation:

The graph is represented as an adjacency list, where each node has a list of edges. Each edge has a destination router and a 
weight (cost/distance).
Dijkstra's Algorithm:

Priority Queue: We use a priority queue (min-heap) to always process the router with the smallest distance first.
Distance Array: A dist array is used to store the shortest distance from the source router to every other router. Initially,
 all distances are set to INT_MAX (infinity), except the source router which has a distance of 0.
Relaxation: For each router, we explore its neighbors and update their distances if a shorter path is found.
Time Complexity: The time complexity of Dijkstra's algorithm is O(E log V) where V is the number of vertices (routers) and E 
is the number of edges (connections).
