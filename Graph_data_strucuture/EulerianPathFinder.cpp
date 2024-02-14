#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include "utility"
#include "unordered_set"


using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjList;
    bool isDirected;
public:
    Graph(bool isD) {
        this->isDirected = isD;
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        if (!isDirected)
            adjList[v].push_back(u);
    }

    // Hash according to first element of pair
    struct pair_hash {
        size_t operator()(const pair<int, int> &p) const {
            return hash<int>{}(p.first);
        }
    };

    // * Check Whether bridge can't break/disconnected
    bool isValidBridge(int u, unordered_set<pair<int, int>, pair_hash> &edges) {
        int validCount = 0; // how many valid neighbours of safeVertex
        for (auto &v: adjList[u]) {
            // check if (u,v) or (v,u) don't exist till end
            if (edges.find({u, v}) == edges.end()
                && edges.find({v, u}) == edges.end()) {
                validCount++;
            }
            // Now We can assume, it is possible to came back
            if (validCount >= 2) {
                return true;
            }
        }
        return false;
    }


    void printEulerPath(int currVertex, unordered_set<pair<int, int>, pair_hash> &edges) {
        // use stack to track the path_finder
//        stack<int> path_finder;


        // I am Starting with Odd Degree Vertex.
        // I will find oddDegreeVertex's such neighbour who had more than 1 Edges to Visit
        // so, it can revert back
        // I will not go for oddDegreeVertex's such neighbour having only 1 Edge to visit,
        // cuz it can't come back then


        int anySafe = -1;
        // SafeNeighbour where I can move and come back
        // if not such move to any available
        for (auto &SafeNeighbour: adjList[currVertex]) {
            // if Neighbour is not already visited yet (u->v) or (v->u)
            if (edges.find({currVertex, SafeNeighbour}) == edges.end()
                && edges.find({SafeNeighbour, currVertex}) == edges.end()) {
                // check whether SafeNeighbour is Valid Bridge
                if (isValidBridge(SafeNeighbour, edges)) {
                    cout << currVertex << " ";
                    edges.insert({currVertex, SafeNeighbour});
                    printEulerPath(SafeNeighbour, edges);
                    return;
                }
                anySafe = SafeNeighbour;
            }
        }

        if (anySafe != -1) {
            cout << currVertex << " ";
            edges.insert({currVertex, anySafe});
            printEulerPath(anySafe, edges);
        }
    }

    void FindEulerPath() {
        int oddDegreeCount = 0;
        int oddDegreeVertex = -1;
        int sumOfDegree = 0;
        unordered_set<pair<int, int>, pair_hash> edges; // to track visited edges

        // Find how many vertex has odd Degree
        for (auto &v: adjList) {
            // summing degree of v vertex
            sumOfDegree += v.second.size();
            // if v points/linked with odd Vertices
            if (v.second.size() % 2 == 1) {
                oddDegreeCount++;
                // save any odd Degree vertex
                oddDegreeVertex = v.first;
            }
        }
        // * According to handShake Theorem
//        Sum(deg(v) for v in V) = 2 * number of edges

        if (oddDegreeCount == 0) {
            printEulerPath(adjList.begin()->first, edges);
            if (sumOfDegree != 2 * edges.size()) {
                cout << "Disconnected Components.\n";
                return;
            }
            cout << "Path and Circuit Both Exist\n";
        } else if (oddDegreeCount == 2) {
            printEulerPath(oddDegreeVertex, edges);
            if (sumOfDegree != 2 * edges.size()) {
                cout << "Disconnected Components.\n";
                return;
            }
            cout << "Only Path Exist.\n";
        } else {
            cout << "Neither Path or Circuit Exist\n";
        }
    }

    void DFS(int vertex, unordered_set<int> &visited) {
        // Mark the current node as visited

        // Print the current node
        cout << vertex << " ";

        // Recur for all the vertices adjacent to this vertex
        for (auto &i: adjList[vertex]) {
            if (visited.find(i) == visited.end()) {
                visited.insert(vertex);
                DFS(i, visited);
            }
        }
    }
};

int main() {

    // inDirected graph
    bool isDirected = false;
    Graph graph(isDirected);

    int numEdges;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter edge from : (u > v) ";
    int u, v;
    for (int i = 0; i < numEdges; i++) {
        while(true) {
            cin >> u >> v;
            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter two integers: ";
            } else if(u >= 0 && v >= 0 ){
                graph.addEdge(u, v);
                break;
            } else {
                cout << "Invalid input. Please enter two non-negative integers: ";
            }
        }
    }
    graph.FindEulerPath();

    cout << "\n Walking around . . .\n";
    unordered_set<int> visited;
    visited.insert(u);
    graph.DFS(u, visited);

}

