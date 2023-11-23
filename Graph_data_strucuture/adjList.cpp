#include <iostream>
#include <unordered_map>
#include <vector>
#include "queue"
#include "stack"

using namespace std;

class Graph {
    bool isDirected;
    unordered_map<int, vector<int>> adjList;
    
        // DFS_Helper Traversal, and return if it's a valid Component
    void DFS_Helper(int node, unordered_map<int, bool> &visited) {

        stack<int> st;
        st.push(node);

        while (!st.empty()) {
            int curr = st.top();
            st.pop();

            // If the node has not been visited yet, mark it as visited and process it
            if (!visited[curr]) {
                visited[curr] = true;
                cout << curr << " ";

                // Push all unvisited neighbours of the node into the stack
                for (int neighbour: adjList[curr]) {
                    if (!visited[neighbour]) {
                        st.push(neighbour);
                    }
                }
            }
        }
        cout << endl;
    }

public:
    Graph(bool isDirected) : isDirected(isDirected) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        if (isDirected)
            adjList[v].push_back(u); // Comment this line for a directed graph
    }

    // node = Starting Node/Index
    void BFS(int node) {
        unordered_map<int, bool> visited;
        queue<int> q;
        q.push(node);
        visited[node] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            // Enqueue all neighbours of Visited Node
            for (int neighbour: adjList[curr]) {
                if (!visited[neighbour]) {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }
            }
        }
        cout << endl;
    }
    

    void DFS_Connected_Components() {
        int totalComponents = 0;
        unordered_map<int, bool> visited;

        for (const auto &entry: adjList) {
            int node = entry.first;
            if (!visited[node]) {
                DFS_Helper(node, visited);
                totalComponents++;
            }
        }
        cout<<"\tTotal Components in Graph -> "<<totalComponents<<endl;
    }

    void printGraph() {
        for (auto i: adjList) {
            cout << " " << i.first << " => ";
            for (int j: i.second) {
                cout <<", "<<j;
            }
            cout << "\n";
        }
    }

};

int main() {
    bool isDirected = false;
    Graph graph(isDirected);
    graph.addEdge(4,9);
    graph.addEdge(3,5);
    graph.addEdge(4,7);
    graph.addEdge(4,5);
    graph.addEdge(3,9);
    graph.addEdge(7,3);
    graph.addEdge(9,3);
    graph.addEdge(3,7);

    graph.addEdge(12,19);
    graph.addEdge(12,16);
    graph.addEdge(12,18);
    graph.addEdge(13,19);
    graph.addEdge(19,18);
    graph.addEdge(16,13);
    graph.addEdge(16,12);


//    graph.printGraph();
//    graph.BFS(12);
    graph.DFS_Connected_Components();

}
