#include "iostream"
#include "AVL_Tree.h"
using namespace std;

int main() {
    AVL_Tree *root = NULL;
    root = InsertInAVL(root, 12);
    root = InsertInAVL(root, 8);
    root = InsertInAVL(root, 4);
    cout << "Printing PreOrder Traversal: \n";
    PreOrderTraversal(root);
    cout << endl;

    root = InsertInAVL(root, 6);
    root = InsertInAVL(root, 2);
    root = InsertInAVL(root, 3);
    root = InsertInAVL(root, 14);
    root = InsertInAVL(root, 16);
    cout << "\nPrinting level Order Traversal: \n";
    levelOrderTraversal(root);

    root = deleteInAVL(root, 8);
    root = deleteInAVL(root, 6);
    root = deleteInAVL(root, 4);

    cout << "After Some Deletion: \n";
    levelOrderTraversal(root);


}
