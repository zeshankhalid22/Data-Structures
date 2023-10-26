#include "iostream"
#include "vector"

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    int height;

    Node(int data) {
        this->data = data;
        left = right = NULL;
        height = 1; // as new Node is initially added at leaf
    }

};

int getHeight(Node *node) {
    if (node == NULL)
        return 0;
    else
        return node->height;
}

// return the difference left & right node's height
int getBalance(Node *node) {
    return getHeight(node->left) - getHeight(node->right);
}

// here in Function let
// T1 > T2 > ( parentNode > medianNode > leaf/updated Node )
Node *leftRotate(Node *parentNode) {
    /*  Initial Example
     *      5 <- parentNode
     *     /  \
     *   (T1)  10  <- medianNode
     *         /  \
             (T2)  15 <- recently Inserted or updated Node
             */

    Node *medianNode = parentNode->right; // parentNode < medianNode < leftNode
    Node *T2 = medianNode->left; // T2 > parentNode

// * Perform Rotation
    medianNode->left = parentNode;
    /*  Now
     * |--- 5
     * v   /  \
     * | (T1)  10  <- medianNode
     * v       /  \
       |      5   15    (address of parentNode is copied in medianNode too)
       v     /
       |---(T1)
   T(2) is saved*/

    parentNode->right = T2;
    /*  Now
     *  medianNode
 *          10
 *        /     \
         5      15
        /  \
      (T1) (T2) */

// * Update Heights
    // first update parent Node cuz it's on left/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode;  // as new root Node
}

// Same leftRotate's Rule will be followed for rightRotate with a minor change
// see leftRotate's comment for more clarity
Node *rightRotate(Node *parentNode) {
    Node *medianNode = parentNode->left;
    Node *T2 = medianNode->right;

// * perform rotation
    medianNode->right = parentNode;
    parentNode->left = T2;

// * Update Heights
    // first update parent Node cuz it's on right/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode; // as new root
}

// Root, Left, Right
void PreOrderTraversal(Node *root) {
    if (root) {
        cout << root->data << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

Node *Insert(Node *root, int val) {
    if (root == NULL)
        return new Node(val);

    if (val < root->data)
        // Root node returned with data and height = 1
        root->left = Insert(root->left, val);
    else if (val > root->data)
        root->right = Insert(root->right, val);
    else    // if value is equal to node itself, no insertion allowed
        return root;

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // | ============================================ |
    //              ** Rotation Cases **

    // 1. handle left skewed unbalanced situation
//           X       Y
//          Y   to  Z X
//         Z
    if (balance > 1 && val < root->left->data){
        root = rightRotate(root);
        return root;
    }

    // 2. handle right skewed unbalanced situation
//       X         Y
//        Y   to  X  Z  (Left Rotate)
//         Z
    if (balance < -1 && val > root->right->data) {
        root = leftRotate(root);
        return root;
    }
    // 3. handle Left, Right  unbalanced situation
//         X            X         Z
//       Y       to,   Z     to Y   X
//         Z.         Y
    if(balance > 1 && val > root->right->data){
        // first rotate root->left and it's child then root
        root->left = leftRotate(root->left);
        root = rightRotate(root);
        return root;
    }

    // 4. handle Right, left  unbalanced situation
//         X         X             Z
//           Y   to,   Z     to  X    Y
//         Z.            Y
    if(balance < -1 && val < root->right->data){
        // first rotate root->right and it's child then root
        root->right = rightRotate(root->right);
        root = leftRotate(root);
        return root;
    }

//  | ============================================ |
    return root;
}

int main() {
    Node *root = NULL;
    root = Insert(root, 7);
    root = Insert(root, 9);
    root = Insert(root, 11);
    PreOrderTraversal(root); cout << endl;
        
    root = Insert(root, 10);
    root = Insert(root, 14);
    root = Insert(root, 17);
    PreOrderTraversal(root);    cout<<endl;

}
