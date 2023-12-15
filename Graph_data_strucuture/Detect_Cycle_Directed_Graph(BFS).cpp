#include <iostream>
#include <unordered_map>
#include <vector>
#include "queue"


using namespace std;

class Graph {
    bool isDirected;
    unordered_map<int, vector<int>> adjList;

public:
    Graph(bool isDirected) : isDirected(isDirected) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        if (!isDirected)
            adjList[v].push_back(u); // Comment this line for a directed graph
    }

    // topological sort using bfs
    void kahns_algo() {
        if (!isDirected) {
            cout << "No Topological Sort (UnDirected graph).\n";
        }
        //        [vertex, degree]
        unordered_map<int, int> inDegree;
        // initial degree of each node = 0
        for (const auto &i: adjList)
            inDegree[i.first] = 0;

        // traverse and add inDegree to each Vertex
        for (const auto &i: adjList) {
            for (int j: i.second) {
                inDegree[j]++;
            }
        }
        vector<int> topSort;   // to store elements in topological order
        queue<int> zeroInDegreeQueue;
        // Pushing all 0 inDegree elements in queue
        for (auto &i: inDegree) {
            if (i.second == 0) {
                inDegree[i.first]--;
                zeroInDegreeQueue.push(i.first);
            }
        }


        while (!zeroInDegreeQueue.empty()) {
            int front = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();

            topSort.push_back(front);
            // insert neighbours
            for (auto neighbours: adjList[front]) {
                inDegree[neighbours]--;
                if (inDegree[neighbours] < 0) {
                    cout << "Cycle detected.\n";
                    return;
                }
                if (inDegree[neighbours] == 0) {
                    zeroInDegreeQueue.push(neighbours);
                }
            }
        }

        if (topSort.size() != adjList.size()) {
            cout << "Cycle Detected.\n";
            return;
        }
// if loop completed, it means Cycle is not Detected
        cout << "Topological Sort -> ";
        for (auto &i: topSort) {
            cout << i << " ";
        }
        cout <<endl;
    }

};

int main() {
    bool isDirected = true;
    Graph graph(isDirected);
    graph.addEdge(4, 11);
    graph.addEdge(11, 13);
    graph.addEdge(13, 15);
//    graph.addEdge(13,4);
    graph.addEdge(7,8);

    graph.kahns_algo();

}
