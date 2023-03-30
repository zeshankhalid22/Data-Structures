#include "iostream"
#include "map"
using namespace std;

    // Function to print size and key:value pair
    void print(map<string,int>&Map){
        cout<<"Map size: "<<Map.size()<<endl;   // Size of Map
        for(auto &it:Map){  // Printing Values
            cout<<"Key: "<<it.first<<", Value: "<<it.second<<endl;
        }
    }
int main(){
    map<string,int> Map;

    //  Map to Store Stationary keys along with their corresponding frequency
    Map["pointer"]=3;
    Map["ballpen"]=2;
    Map["marker"]=1;
    Map["register"]=4;
    Map["register"]=6;  // Value will be replaced
    Map["mouse"];   // "mouse" is inserted in Map  with an empty string value

    print(Map); // Calling print function
    auto it2 = Map.find("mouse"); // Find value of inserted key
    cout<<"\nFind Value.  Key: "<<it2->first<<", Value: "<<it2->second<<endl;

    Map.erase("pointer");   // just remove Value at inserted Key
    Map.erase("ballpen");

    auto it = Map.find("marker");
    Map.erase(it);       // Delete the whole pair of "marker"

    cout<<"\n - - - Printing Again - - -\n";
    print(Map);


}
