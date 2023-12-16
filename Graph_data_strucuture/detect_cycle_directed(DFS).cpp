#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjList;
    // Check whether some Path is tried to visited again (DFS)
    bool path_vis_again(int v, unordered_map<int, bool> &visited, unordered_map<int, bool> &path_finder) {

        // visit and set current V's path_finder
        visited[v] = true;
        path_finder[v] = true;
        for (auto neighbours: adjList[v]) {
            if (!visited[neighbours]) {
                // go in neighbours path_finder
                bool ret = path_vis_again(neighbours, visited, path_finder);
                // if cycle detected from neighbours, no need to go more, just return
                if (ret)
                    return true;
            }
                // if we are coming [again] to visited, path_finder. it is Cycle
            else if (path_finder[neighbours]) {
                return true;
            }
        }
        // leaving vertex, mean leaving/backtracking this path,
        // so remove curr v from path_finder, as cycle not detected at this point
        path_finder[v] = false;
        return false;
    }

public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    bool isCycle() {
        int V = adjList.size();
        unordered_map<int, bool> visited;
        unordered_map<int, bool> path_finder;   // to keep track of current path

        for (int i = 0; i < V; i++) {
            // check for every non-visited node
            if (!visited[i]) {
                bool ret = path_vis_again(i, visited, path_finder);
                // ang time ret is true, means cycle detected, return
                if (ret)
                    return ret;
            }
        }
        return false;
    }


};

int main() {

    Graph graph;
    unsigned int edges;
    cout<<"Detect Cycle in Directed Graph (DFS)\n";
    cout << "Enter number of Edges > ";
    cin >> edges;
    cout << "Enter " << edges << " (u -> v) pairs:\n";
    while (edges--) {
        int u, v;
        cout << " > ";
        cin >> u >> v;
        graph.addEdge(u, v);
    }


    bool ans = graph.isCycle();
    if (ans) {
        cout << "Cycle Detected.\n";
        return 0;
    }
    cout << "Cycle not Detected\n";


}
