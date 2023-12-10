#include <iostream>
#include <unordered_map>
#include <vector>
#include "queue"

using namespace std;

class DirectedGraph {
    unordered_map<int, vector<int>> adjList;

    // Check whether some Path is tried to visited again (DFS)
    bool path_vis_again(int v, unordered_map<int, bool> &visited, unordered_map<int, bool> &path) {

        // visit and set current V's path
        visited[v] = true;
        path[v] = true;
        for (auto neighbours: adjList[v]) {
            if (!visited[neighbours]) {
                // go in neighbours path
                bool ret = path_vis_again(neighbours, visited, path);
                if (ret)
                    return true;
            }
                // if we are coming [again] to visited, path. it is Cycle
            else if (path[neighbours]) {
                return true;
            }
        }
        // leaving vertex, mean leaving this path
        path[v] = false;
        return false;
    }

public:

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // topological sort using bfs, also check whether cycle detected or not
    bool kahns_algo() {
        //        [vertex, degree]
        unordered_map<int, int> inDegree;
        int count = 0;
        
        // initial degree of each node = 0
        for (const auto &i: adjList)
            inDegree[i.first] = 0;

        // traverse and add inDegree to each Vertex
        for (auto &i: adjList) {
            for (auto &j: i.second) {
                // Increment inDegree of each adjacent vertex
                inDegree[j]++;
            }
        }

        queue<int> zeroInDegreeQueue;

        // Pushing all 0 inDegree elements in queue
        //         [ vertex, degree ]
        for (auto i: inDegree)
            if (i.second == 0)
                zeroInDegreeQueue.push(i.first);

        while (!zeroInDegreeQueue.empty()) {
            int front = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();

            count++;
            // insert neighbours of front
            for (auto neighbours: adjList[front]) {
                inDegree[neighbours]--; // reduce neighbours inDegree
                if (inDegree[neighbours] == 0)
                    zeroInDegreeQueue.push(neighbours);
            }
        }

        // check whether all the elements are counted
        // if not, it means Cycle exist
        if (this->adjList.size() == count)
            return true;
        else
            return false;
    }

    bool isCycle() {
        int V = adjList.size();
        unordered_map<int, bool> visited;
        unordered_map<int, bool> path;

        for (int i = 0; i < V; i++) {
            // check for every non-visited node
            if (!visited[i]) {
                bool ret = path_vis_again(i, visited, path);
                if (ret)
                    return ret;
            }
        }
        return false;
    }


};

int main() {
    DirectedGraph graph;
    unsigned int edges;
    cout << "Enter number of Edges > ";
    cin >> edges;
    cout << "Enter " << edges << " (u -> v) pairs:\n";
    while (edges--) {
        int u, v;
        cout << " > ";
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    int choice;
    cout << "Wanna detect Cycle through [0. DFS,  1. BFS] > ";
    cin >> choice;
    if (choice == 0) {
        bool ans = graph.isCycle();
        if (ans) {
            cout << "Cycle Detected.\n";
            return 0;
        }
        cout << "Cycle not Detected\n";
    } else if (choice == 1) {
        if (graph.kahns_algo()) {
            cout << "Cycle Detected.\n";
            return 0;
        }
        cout << "Cycle not Detected\n";
    } else {
        cout << "No other Option.\n";
        return 0;
    }


}
