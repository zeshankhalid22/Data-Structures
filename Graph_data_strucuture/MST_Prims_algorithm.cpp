#include <climits>
#include "iostream"
#include "vector"
#include "unordered_map"
#include "queue"

using namespace std;

class Graph {
    unordered_map<int, vector<pair<int, int>>> adjList;
public:
    void addEdge(int u, int v, int w) {
        adjList[u].push_back(make_pair(v, w));
        adjList[v].push_back(make_pair(u, w));
    }

    void prims_algorithm_solver(int src) {
        // invalid source
        if (src >= adjList.size() -  1 || adjList[src].size() == 0)
            return;

        // to store minimum possible weights to reach that vertex from any source
        vector<int> minWeights(adjList.size(), INT_MAX);
        // to mark added elements in MST, so we can't visit again
        vector<bool> inMST(adjList.size(), false);

        // min heap to store weights of vertices that are not included in MST yet
        //          [min weight , vertex]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<> > pq;

        // * Data Structures of Extra features
        // temp adjacency list to hold final MST
        unordered_map<int, vector<pair<int, int>>> mstAdjList;
        // Vector to store the order of inclusion in MST
        vector<int> mstOrder;
        // parent vertex of v is the parent with minimum weight
        vector<int> parentVertex(adjList.size(), -1);   // the min-cost/effort Edge for each vertex

        // starting with src index
        minWeights[src] = 0;
        parentVertex[src] = -1;
        pq.push(make_pair(0, src));// insert source itself with min weight from itself
        mstOrder.push_back(src);
        
        while (!pq.empty()) {
            int minWeightedVertex = pq.top().second; // recently added having min weight
            pq.pop();
            inMST[minWeightedVertex] = true;    // include vertex in MST
            // include minWeightedVertex's neighbour's min Weight in pq
            for (auto &neighbour: adjList[minWeightedVertex]) {
                int neighbourVertex = neighbour.first;
                int weight = neighbour.second;

                // there's a chance that Weight of curr U->V is smaller
                // than the previous weight going towards neighbourVertex,  if yes, update
                if (!inMST[neighbourVertex] && weight < minWeights[neighbourVertex]) {
                    pq.push({weight, neighbourVertex});
                    // U is new Parent/link of V bcz of min possible weight
                    parentVertex[neighbourVertex] = minWeightedVertex;

                    mstOrder.push_back(neighbourVertex);  // add vertex in order
                    // add new edges to temp MST adjacency list
                    mstAdjList[minWeightedVertex].push_back({neighbourVertex, weight});
                    mstAdjList[neighbourVertex].push_back({minWeightedVertex, weight});
                }
            }
        }

        // replace temp MST list with original Adjacency List
        adjList.clear();
        adjList = mstAdjList; // O(E)

        cout << "Order of Vertexes inclusion in MST > ";
        for (int v: mstOrder) {
            cout << v << " ";
        }
        cout << endl;

        cout << "\tVertex\tParent/link(Min weight)\n";
        for (int i = 0; i < parentVertex.size(); i++) {
            if (i == src)
                cout << "\t" << i << "\t\t" << "Source" << endl;
            cout << "\t" << i << "\t\t" << parentVertex[i] << endl;
        }
        cout << "\t-----------------\n";

    }
};

int main() {
    Graph graph;

    int u, v, w, e;
    cout << "How many Edges > ";
    cin >> e;
    cout << "Enter (U > V > W): \n";
    while (e--) {
        cout << "\t> ";
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    cout << "Enter Source to start > ";
    cin >> u;
    graph.prims_algorithm_solver(u);
}
