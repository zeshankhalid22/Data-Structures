#include "iostream"
#include "climits"

using namespace std;

class Heap {
    int *arr;
    int Capacity;
    int size;
public:
    Heap(int size) {
        this->Capacity = size;
        this->size = 0;
        arr = new int[size];
    }

    int getMin() { return arr[0]; }

    void insertKey(int val) {
        if (Capacity == size) {
            cout << "Heap is full" << endl;
            return;
        }

        size++;
        // Capacity is 1 based, currIndex is 0 based
        int currIndex = size - 1;
        arr[currIndex] = val;

        // here parent = (currIndex - 1) / 2;
        while (currIndex != 0 && arr[(currIndex - 1) / 2] > arr[currIndex]) {
            swap(arr[(currIndex - 1) / 2], arr[currIndex]);
            currIndex = (currIndex - 1) / 2;
        }

    }

    // removes and return minimum element
    int extractMin() {
        if (size < 1)
            return INT_MIN;

        int minVal = arr[0];
        arr[0] = arr[size - 1];   // move last element at root
        size--; // as last element removed, decrement Capacity

        // now heap is unbalanced, Balance it
        Heapify(0);
        return minVal;

    }

    void decreaseKey(int index, int val){
        // value at given index is already smaller
        if(arr[index] < val)
            return;
        // out of bound index
        if (index >= size)
            return;

        arr[index] = val;
        while(index!=0 && arr[index] < arr[(index-1)/2]){
            swap(arr[index],arr[(index-1)/2]);
            index = (index-1)/2;
        }
    }
    void Heapify(int currIndex) {
        int leftChild = (2 * currIndex) + 1;
        int rightChild = (2 * currIndex) + 2;
        int minIndex = currIndex;

        // below 2 conditions will find SMALLER element
        // between Left & Right childNodes of CurrentNode
        if (leftChild < size && arr[leftChild] < arr[minIndex])
            minIndex = leftChild;
        if (rightChild < size && arr[rightChild] < arr[minIndex])
            minIndex = rightChild;

        if (minIndex != currIndex) {
            swap(arr[minIndex], arr[currIndex]);
            Heapify(minIndex);
        }
    }

    void deletebyIndex(int index){
        if(index < 0 || index >= size)
            return;

        decreaseKey(index,INT_MIN);
        extractMin();
    }

    void levelOrderDisplay() {
        int endOfLevel = 0;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
            if (i == endOfLevel) {
                cout << endl;
                endOfLevel = (endOfLevel * 2) + 2;
            }
        }
        cout << endl;
    }
};

int main() {
    Heap heap(37);
    heap.insertKey(12);
    heap.insertKey(28);
    heap.insertKey(32);
    heap.insertKey(24);
    heap.insertKey(46);
    heap.insertKey(16);
    heap.insertKey(42);

    heap.levelOrderDisplay();
    heap.decreaseKey(6,25);
    heap.decreaseKey(4,40);
    heap.decreaseKey(1,18);
    cout<<"After Decreasing Some Values\n";
    heap.levelOrderDisplay();

    cout<<"After Deleting Some Indexes\n";
    heap.deletebyIndex(4);
    heap.deletebyIndex(3);
    heap.levelOrderDisplay();

}
