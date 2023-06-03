#include "iostream"
using namespace std;

int calculatePower(int num, int pow){
    // BASE Cases
    if (pow == 0)
        return 1;
    if(pow == 1)
        return num;

    if(pow%2==0){   // Even power , num ^ pow = num ^ (pow/2)  +  num ^ (pow/2) 
        int ans = calculatePower(num,pow/2);
        return ans * ans;
    }
    else{       // ODD power   ,    num ^ pow = num * num ^ (pow/2)  +  num ^ (pow/2)
        int ans = calculatePower(num,pow/2);
        return num * ans * ans;
    }
}

bool is_sorted(int *arr,int n){
    if(n==1)    // means every element compared and true, and finally arr is sorted
        return true;

    if(arr[n-2] > arr[n-1]) // prev element is greater than next, not sorted
        return false;

    else{
        bool ans = is_sorted(arr,n-1); // go on calling next elements
        return ans;
    }

}

// print half array divided by binary search
void print_s_to_e(int *arr,int s, int e){
    for(int i=s; i<=e; i++){
        cout<<arr[i]<<" ";
    }
    cout<<", mid="<<arr[s+e/2]<<endl;
}

int binary_search(int *arr, int st, int ed, int value){
    print_s_to_e(arr,st,ed);    // first print the given array

    if(st > ed)
        return -1;

    int md = st + ( ed - st ) / 2;
    if(arr[md]==value)
        return md;
    else if(arr[md] > value){   // go on left side
        return binary_search(arr,st,md - 1,value);
    }
    else    // go on right side
        return binary_search(arr,md + 1,ed,value);

}

int main(){

    // * is_sorted()
    int arr[] = {1,2,8,4,5};
    int size = sizeof(arr)/sizeof(int);
    if(is_sorted(arr,size))
        cout<<"Sorted\n\n";
    else
        cout<<"Not sorted\n\n";

    //     * binary_search()
    int arr2[] = {2,4,5,7,8,12,15,18};
    int size2 = sizeof(arr)/sizeof(int);

    int value = 2;
    int temp = binary_search(arr,0,size-1,value);

    if(temp==-1)
        cout<<"! Value not found.\n";
    else
        cout<<"Value, " <<value <<" found at Index: "<< temp <<endl<<endl;

    // * calculate_power()
    int num = 2, pow = 9;
    cout<<num <<" raise power "<< pow << " is : " <<calculatePower(num,pow)<<endl<<endl;

}
