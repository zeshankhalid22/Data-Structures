#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
#include "queue"


using namespace std;

class Graph {

    //             U ->    [{V1, dist},{V2, dist}, . . . ,{Vx, dist}]
    //             U2 ->   [{V1, dist},{V2, dist}, . . . ,{Vx, dist}]
    //             Ux ->   [{V1, dist},{V2, dist}, . . . ,{Vx, dist}]
    unordered_map<int, vector<pair<int, int>>> adjList;


public:
    Graph() {}

    void addEdge(int u, int v, int dist) {
        //      u       ->   {v, dist}
        adjList[u].push_back({v, dist});
    }

    // return weight of u -> v if they exist, otherwise -1
    int weight(int u, int v) {
        // iterate into U's neighbour
        for (auto &i: adjList[u]) {
            // if U -> V found
            if (i.first == v) {
                return v.second;
            }
        }
        return -1;
    }

    // Kahn's algorithm
    vector<int> top_sort_bfs() {
        //        [vertex, degree]
        unordered_map<int, int> inDegrees;
        // initial degree of each node = 0
        for (const auto &V: adjList)
            inDegrees[V.first] = 0;

        // Calculate InDegree(no in-coming Nodes towards V)
        for (auto &U: adjList) {
//            U -> [{V1, dist}, {V2, dist}, {V3, dist} . . ]
            for (auto &V: U.second) {
                inDegrees[V.first]++;    // inDegrees[Vi]++
            }
        }

        vector<int> topSort;   // to store elements in topological order
        queue<int> zeroInDegreeQueue;
        // Pushing all 0 inDegrees elements in queue
        //          i = [V -> in degree]
        for (auto &i: inDegrees) {
            if (i.second == 0) {
                inDegrees[i.first]--;   // decrement degree
                zeroInDegreeQueue.push(i.first);    // q.push(V having 0 in degree
            }
        }

        // Finding topological Order
        while (!zeroInDegreeQueue.empty()) {
            int front = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();

            topSort.push_back(front);
            // insert neighbour vertex [Vertex, Dist]
            for (auto neighbours: adjList[front]) {
                inDegrees[neighbours.first]--;  // inDegrees[neighbour vertex]--
                if (inDegrees[neighbours.first] < 0) {
                    // neighbour is tried to be visited more times than it's inDegree/it should
                    // Cycle Detected here, return as it is
                    return topSort;
                }
                // push neighbour vertices having inDegree 0
                if (inDegrees[neighbours.first] == 0)
                    zeroInDegreeQueue.push(neighbours.first);
            }
        }
        // if topSort.size==adjList.size() it means Acyclic graph
        // otherwise Cycle detected
        return topSort;
    }

    // Find Shortest Path from Source(less independent Vertex) to Dest(Dependent Vertex)
    // * Weighted Directed Graph
    void path_finder() {
        /// less InDependent Vertices (Topological Order) will be solved first

        // grand parent -> parent -> child like Sort
        vector<int> topSort = top_sort_bfs();
        if (topSort.size() != adjList.size()) {
            cout << "Cycle Detected.\n";
            return;
        }

        //given  Source to [vert, dist]
        unordered_map<int, int> distance;
        // Assume distance of all vertices is INFINITY
        for (auto &i: adjList) {
            // [Vertex, dist=INFINITY]
            distance.insert({i.first, INT_MAX});
        }

        // Calculate all Vertex's Dist from Source
        // topSort[0] is Source for Directed Graph
        distance[topSort[0]] = 0;   // Dist from Source to itself is 0

        // for every vertex  U/Parent in Topological Sort(less independent first)
        for (auto &U: topSort) {
            // for every neighbour/child V of U/Parent
            for (auto &V: adjList[U]) {

                if (distance[V.first] > distance[U] + weight(U, V.first)) {
                    // bcz there's some distance shorter than [V.first], so update
                    distance[V.first] = distance[U] + weight(U, V.first);
                }
            }
        }

        // * Printing Distance from Source to Destinations
        cout<<"Distance from ["<<topSort[0]<<"]:\n";
        for(auto &i:distance){
            cout<<"to "<<i.first<<" is "<<i.second<<endl;
        }
        cout<<"\n\t------------------------\n";
    }
};

int main() {

    Graph graph;


    int d, u, v, e;

    cout << "How Many Edges > ";
    cin >> e;

    while (e--) {
        cout << "Enter (U > V > Dist ) > ";
        cin >> u >> v >> d;
        graph.addEdge(u, v, d);
    }

    cout << "Weighted, Directed Graph, Distance from Source to All Vertices.\n ";
    graph.path_finder();


}
