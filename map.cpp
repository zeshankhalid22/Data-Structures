#include "iostream"
#include "map"
#include "unordered_map"
using namespace std;

// Function to printMap size and key:value pair
void printMap(map<string,int>&Map){
    cout<<"Map size: "<<Map.size()<<endl;   // Size of Map
    for(auto &it:Map){  // Printing Values
        cout<<"Key: "<<it.first<<", Value: "<<it.second<<endl;
    }
}
void printUmap(unordered_map<string,int>&umap){
    cout<<"\n\t- - - - - -\n";
    for(auto &it:umap){
        cout<<"Key: "<<it.first<<", Value: "<<it.second<<endl;
    }
}

void ordered_map(){
    map<string,int> Map;
    //  Map to Store Stationary keys along with their corresponding frequency
    Map["pointer"]=3;
    Map["ballpen"]=2;
    Map["marker"]=1;
    Map["register"]=4;
    Map["register"]=6;  // Value will be replaced
    Map["mouse"];   // "mouse" is inserted in Map  with an empty string value

    printMap(Map); // Calling printMap function
    auto it2 = Map.find("mouse"); // Find value of inserted key
    cout<<"\nFind Value.  Key: "<<it2->first<<", Value: "<<it2->second<<endl;

    Map.erase("pointer");   // just remove Value at inserted Key
    Map.erase("ballpen");

    auto it = Map.find("marker");
    Map.erase(it);       // Delete the whole pair of "marker"

    cout<<"\n - - - Printing Again - - -\n";
    printMap(Map);

}

void unorderedMap(){
    // Declare unordered map and initilize 2 pairs
    unordered_map<string,int> umap{
            {"DLD",60},
            {"Islamyat",75},
    };

    cout<<"Old Marks: "<<endl;
    cout<<"DLD : "<<umap["DLD"]<<endl
        <<"Islamyat: "<<umap["Islamyat"]<<endl;

        // * Updating Values
        umap["DLD"]=66; // [] operator assign Garbage value is specified key doesn't exist
        umap.at("Islamyat") += 10;  // increment value by 10

        // * Inserting Pairs
        umap["Math"]=55;
        umap.insert({{"English",77},{"OOP",87}});

        // * Displaying Elements
    printUmap(umap);

}
int main(){
    // Functions demonstrating ordered and unordered map
    
    ordered_map();
//    unorderedMap();
}
