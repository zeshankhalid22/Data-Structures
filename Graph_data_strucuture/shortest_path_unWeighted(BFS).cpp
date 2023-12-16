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

    // shortest distance UnWeighted Graph, from src to all
    // assume dist from every U to V is 1.
     void distanceFromSource(int src){
         if(adjList.find(src) == adjList.end()){
             cout<<"Invalid Source\n";
             return;
         }

         unordered_map<int,bool> visited;
         //           <vertex, distance from src>
         unordered_map<int,int> distance;
         // initial distance -1
         for(auto &i: adjList){
        distance[i.first] = -1;
    }

         queue<int> q;
         q.push(src);
         distance[src] = 0;
         visited[src] = true;

         while(!q.empty()){
             int u =  q.front();
             q.pop();

             for(auto &neighbour: adjList[u]){
                 if(!visited[neighbour]){
                 // neighbour distance = dist[currVertex] + 1
                     distance[neighbour] = distance[u] + 1;
                 // push neighbour in q, so it's neighbour also be traversed
                 q.push(neighbour);
                 visited[neighbour] = true;
                 }
             }
         }
         cout << "Shortest Distance from [" << src << "] to\n";
         for(auto &i: distance){
             cout<<i.first<<" is "<<i.second<<endl;
         }
         cout<<"\n\t----------------------\n";
     }




 };

 int main() {
     bool isDirected = true;
     cout<<"0: UnDirected,  1: Directed  > ";
     cin>>isDirected;
     if(isDirected)
         cout<<"Enter values in Topological Sort.\n";

     Graph graph(isDirected);

     cout<<"How many Edges > ";
     int edges,u,v,src;
     cin>>edges;
     cout<<"Enter "<<edges<<" Edges in (u -> v ) form\n";
     while(edges--){
         cout<<" > ";
         cin>>u>>v;
         graph.addEdge(u,v);
     }

     cout<<"Enter Valid Source > ";
     cin>>src;


     graph.distanceFromSource(src);


 }

