#include "iostream"
using namespace std;

// from given currIndex, Heapify towards down
void Heapify(int vec[], int size, int currIndex) {
    int leftChild = (2 * currIndex) + 1;
    int rightChild = (2 * currIndex) + 2;
    int maxIndex = currIndex;

    // below 2 conditions will find SMALLER element
    // between Left & Right childNodes of CurrentNode
    if (leftChild < size && vec[leftChild] > vec[maxIndex])
        maxIndex = leftChild;
    if (rightChild < size && vec[rightChild] > vec[maxIndex])
        maxIndex = rightChild;

    // minIndex is some Child, if it is less than parent, swap it
    if (maxIndex != currIndex) {
        swap(vec[maxIndex], vec[currIndex]);
        Heapify(vec, size, maxIndex);
    }
}

// build Heap property from given vector(random values)
void buildMaxHeap(int vec[], int size) {
    // start by Index of Last Non-Leaf TreeNode
    int startIdx = (size / 2) - 1;
    for (int i = startIdx; i >= 0; i--) {
        // Heapify downward from curr(i) idx
        Heapify(vec, size, i);
    }
}

void heapSort(int vec[], int size) {
    buildMaxHeap(vec, size); 

    // swap Max/first element with lastIndex, then heapify
    // from new first element till Max(which is now lastIndex)
    for (int i = size - 1; i >= 0; i--) {
        swap(vec[0],vec[i]);
        // call the Heapify on Reduced Heap
        // here i is the new reduced size
        Heapify(vec,i,0);
    }

}

void levelOrderDisplay(int vec[], int size) {
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


int main() {
    int vec[] = {13, 18, 9, 6, 14, 22, 19};
    int n = sizeof(vec) / sizeof(int);

    heapSort(vec,n);
    levelOrderDisplay(vec, n);
}
