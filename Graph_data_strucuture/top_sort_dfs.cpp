#include "iostream"
#include <stack>
#include "vector"
#include "unordered_map"
using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, bool> visited;
    stack<int> Stack;

public:

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void dfs(int currNode) {
        visited[currNode] = true;

        for (int neighbour = 0; neighbour < adjList[currNode].size(); neighbour++) {
            // visit all dependent/neighbour Nodes of CurrNode, that are not visited yet
            if (!visited[adjList[currNode][neighbour]]) {
                dfs(adjList[currNode][neighbour]);
            }
        }
        
        // push while backtracking from (last to first)
        Stack.push(currNode);
    }

    void topologicalSort() {
        // to visit every SubComponent of graph
        for (auto &i : adjList) {
            if (!visited[i.first]) {
                dfs(i.first);
            }
        }

        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

int main() {
    Graph graph;
    graph.addEdge(4,2);
    graph.addEdge(7,4);
    graph.addEdge(9,4);
    graph.addEdge(2,7);

    graph.addEdge(1,8);


    graph.topologicalSort();
}
