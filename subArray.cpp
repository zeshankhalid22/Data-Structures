// * replacing SubArray's smallest to largest Sum by itself using Cumulative approach
// arr={1,2,3}  → arr={1,3,6} by 1,2+1,3+2+1
#include "iostream"
using namespace std;
// * Sub Array elements are contiguous elements of an array
void sum_sub_array(int n){ // Largest sum Among subArrays using Cumulative approach
    int arr[n];
    cout<<"Array input till "<<n<<": ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
// Traversing Array
    cout<<"Before sum: { ";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<", ";
    }

    for(int i=1;i<n;i++) {
        arr[i] += arr[i-1];  // Any index += with their previous index
    }
// Traversing Array
  cout<<"}\n After sum: { ";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<", ";
    }
// As we are adding element to the next element, sum will be the last element
cout<<"}\nLargest Sum is Last element: "<<arr[n-1]<<endl;
    // ! Note! it will only sort and calculate largest sum for Positive numbers only
}
int main(){
    int n;
    cin>>n;
    sum_sub_array(n);// Print Sums of subArrays for a given length
}