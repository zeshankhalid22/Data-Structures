#include "iostream"
using namespace std;

int partition(int arr[], int st, int ed){
    int pivotValue = arr[st];

    int cnt = 0;
    // Count numbers less than pivotValue
    for(int i=st+1; i<=ed; i++){
        if(arr[i] < pivotValue)
            cnt++;
    }

    int pivotIndex = st + cnt;  // where pivotValue will be shifted/swapped
    swap(arr[st],arr[pivotIndex]);  // swapping 1st(pivotValue) with original pivotIndex

    int i=st, j = ed;
    while(i < pivotIndex && j > pivotIndex){

        // find left value who is greater than pivotValue, bcz want to move it to right
        while(arr[i] <= arr[pivotIndex])
            i++;

        // find right value . . .
        while(arr[j] > arr[pivotIndex])
            j++;

        swap(arr[i++],arr[j--]);

    }
    return pivotIndex;
}

void quickSort(int *arr, int st, int ed){
    // Base Condition
    if(ed <= st)
        return;

    int pivot_index = partition(arr, st, ed);

    // Left part sort
    quickSort(arr,st,pivot_index-1);
    // Right part
    quickSort(arr,pivot_index+1,ed);

}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main(){

     int arr[] = {6, 7, 1, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: \n";
    printArray(arr, n);

}
