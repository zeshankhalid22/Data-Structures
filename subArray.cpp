#include "iostream"
using namespace std;
// * How to print sub Array elements
// * Sub Array elements are contiguous elements of an array
void sum_sub_array(int n){
    int arr[n];
    cout<<"Array input till "<<n<<": ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int sum;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=i;j<n;j++){
            for(int k=i;k<=j;k++){
                cout<<arr[k]<<" ";
            }

            cout<<endl;
        }
    }
}
int main(){
    int n;
    cin>>n;
    sum_sub_array(n);// Print subArray for a given length
}