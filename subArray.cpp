// * Sub Array elements are contiguous elements of an array
#include "iostream"
using namespace std;

void max_sum_BrutForce(int n){ // O(N^3) Largest sum Among subArrays using Brut force approach.
    int arr[n];
    cout<<"\nFinding Largest sum Among subArrays using Brut force approach O(n^3)"<<endl;
    cout<<"input array elements for max_sum_of_subArray(): ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int sum;
    int greaterSum=0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            sum=0;
            cout<<"subArray {";   // to merge with next arr[k]
            for(int k=i;k<=j;k++){
                cout<<" "<<arr[k]; // print subArray elements in a row
                sum+=arr[k];                // sum of that subArray
            }
            cout<<" } (sum: ) "<<sum;
            cout<<"\n";
            if(sum > greaterSum){ //
                cout<<"..........largest Sum is " <<sum<<" for data elements: ";
                for (int k = i; k <= j; k++) {
                    cout<<" "<<arr[k];
                }
                greaterSum=sum;
                cout<<"\n";
            }
            cout<<"\n";
        }
    }
    cout<<"\nFinally "<<greaterSum<<" is the Largest Sum of SubArray!\n";
}

void max_sum_Commulative(int n){ // O(N^2) Largest sum Among subArrays using Cumulative approach
// * replacing SubArray's smallest to the largest Sum by itself using Cumulative approach
// arr={1,2,3}  → arr={1,3,6} by 1,2+1,3+2+1
    int arr[n];
    cout<<"\nFinding Largest sum Among subArrays using Cumulative approach O(n)\n";
    cout<<"Array elements for sum_sub_array "<<n<<": ";
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
    cout<<"}\nFinally Last element "<<arr[n-1]<<" is the Largest Sum of SubArray!\n";
    // ! Note! it will only sort and calculate the largest sum for Positive numbers only
}
int max_sum_kadane(int n){ // O(N) maximum sum using kadane algorithm
    int Sum=0,currSum=0;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<n;i++){
        currSum+=arr[i];
        if(currSum<0)
            currSum=0;
        if(currSum>Sum)
            Sum=currSum;
    }
    return Sum;
}
int main(){
    int n;
    char complexity;
    cout<<"Enter the number of elements: ";
    cin>>n;
    cout<<"Which complexity you wanna use \n1. O(N^3)\n2.O(N^2)\n3.O(N)\n";
    cin>>complexity;
   if(complexity=='1')
       max_sum_BrutForce(n);
   else if(complexity=='2')
       max_sum_Commulative(n);
   else if(complexity=='3')
       cout<<max_sum_kadane(n);
   else
       cout<<"Wrong input.";
}
