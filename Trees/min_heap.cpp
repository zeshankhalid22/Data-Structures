#include "iostream"
#include "climits"

using namespace std;

class Heap {
    int *vec;
    int Capacity;
    int size;
public:
    Heap(int size) {
        this->Capacity = size;
        this->size = 0;
        vec = new int[size];
    }

    int getMin() { return vec[0]; }

    void insertKey(int ID) {
        if (Capacity == size) {
            cout << "Heap is full" << endl;
            return;
        }

        // Insert the new key at the end
        // size follow 1 based indexing, how many total elements are there
        size++;
        int currIndex = size - 1;
        vec[currIndex] = ID;

        // go upward, and re-arrange heap property if violated
        // here parent = (currIndex - 1) / 2;
        while (currIndex != 0 && vec[(currIndex - 1) / 2] > vec[currIndex]) {
            swap(vec[(currIndex - 1) / 2], vec[currIndex]);
            currIndex = (currIndex - 1) / 2;
        }

    }

    // removes and return minimum element
    int extractMin() {
        if (size < 1)
            return INT_MIN;

        // store the start idx/min value, and remove it
        int minVal = vec[0];
        vec[0] = vec[size - 1];   // move last element at root
        size--; // as last element removed, decrement Capacity

        // now heap is unbalanced, Balance it
        Heapify(0);
        return minVal;

    }

    void decreaseKey(int index, int ID){
        // ID at given index is already smaller
        if(vec[index] < ID)
            return;
        // out of bound index
        if (index >= size)
            return;

        vec[index] = ID;

        // go upward, and re-arrange heap property if violated
        // here parent = (currIndex - 1) / 2;
        while(index!=0 && vec[index] < vec[(index-1)/2]){
            swap(vec[index],vec[(index-1)/2]);
            index = (index-1)/2;
        }
    }
    void Heapify(int currIndex) {
        int leftChild = (2 * currIndex) + 1;
        int rightChild = (2 * currIndex) + 2;
        int minIndex = currIndex;

        // below 2 conditions will find SMALLER element
        // between Left & Right childNodes of CurrentNode
        if (leftChild < size && vec[leftChild] < vec[minIndex])
            minIndex = leftChild;
        if (rightChild < size && vec[rightChild] < vec[minIndex])
            minIndex = rightChild;

        // minIndex is some Child, if it is less than parent, swap it
        if (minIndex != currIndex) {
            swap(vec[minIndex], vec[currIndex]);
            Heapify(minIndex);
        }
    }

    void deletebyIndex(int index){
        if(index < 0 || index >= size)
            return;
        
        // Value of [given idx] = INT_MIN, so it came to top/start
        decreaseKey(index,INT_MIN);
        // now given index(with INT_MIN value) is at top, remove it
        extractMin();
    }

    void levelOrderDisplay() {
        int endOfLevel = 0;
        for (int i = 0; i < size; i++) {
            cout << vec[i] << " ";
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
