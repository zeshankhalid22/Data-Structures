#include "iostream"
#include "unordered_set"
using namespace std;


int main(){
    // Declare an unordered set and assign some values
    unordered_set<int> numbers {1,5,6,45,64,1};

    numbers.insert({4, 5, 6});      // inserting multiple values

    for(auto &num:numbers){
        cout<<num<<", ";
    }

    numbers.erase(1); // removing elements from set
    numbers.erase(4);
    numbers.erase(5);

    cout<<"\n- - - Printing again after values removal - - -\n";
    for(auto &num:numbers){
        cout<<num<<", ";
    }cout<<endl;

    // count() return 1 if found, otherwise 0
    if(numbers.count(4))
        cout<<"Found"<<endl;
    else
        cout<<"Not found"<<endl;
}
