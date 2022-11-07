#include "iostream"
using namespace std;
// * How to print sub Array elements
// * Sub Array elements are contiguous elements of an array
void sum_sub_array(int n){ // Largest sum Among subArrays using brute-force approach
    int arr[n];
    cout<<"Array input till "<<n<<": ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int sum;
    int sum2=0;
    for(int i=0;i<n;i++){
        sum=0;
        for(int j=i;j<n;j++){
            for(int k=i;k<=j;k++){
                sum +=arr[k]; // Add sum of a subArray
//                cout<<arr[k]<<" "; // print SubArrays
            }
            if(sum>sum2){           // if sum is getting bigger then sum2(previous sum)
                sum2=sum;           // it's value is stored in sum2.
                sum=0;              // sum will be 0 to store next subArray's values
                                    // for availability to compare it with previous great sum in (sum2)
            }
//            cout<<endl;
        }
    }
    cout<<"Largest sum among subArray using brut-force approach: "<<sum2<<endl;
}
int main(){
    int n;
    cin>>n;
    sum_sub_array(n);// Print Sum and subArray for a given length
}