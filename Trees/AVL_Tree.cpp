#include "iostream"
#include "vector"
#include "queue"

using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode(int val) {
        this->val = val;
        left = right = NULL;
        height = 1; // as new TreeNode is initially added at leaf
    }

};

int getHeight(TreeNode *node) {
    if (node == NULL)
        return 0;
    else
        return node->height;
}

// return the difference left & right node's height
int getBalance(TreeNode *node) {
    return getHeight(node->left) - getHeight(node->right);
}

// here in Function let
// T1 > T2 > ( parentNode > medianNode > leaf/updated TreeNode )
TreeNode *leftRotate(TreeNode *parentNode) {
    /*  Initial Example
     *      5 <- parentNode
     *     /  \
     *   (T1)  10  <- medianNode
     *         /  \
             (T2)  15 <- recently Inserted or updated TreeNode
             */

    TreeNode *medianNode = parentNode->right; // parentNode < medianNode < leftNode
    TreeNode *T2 = medianNode->left; // T2 > parentNode

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
    // first update parent TreeNode cuz it's on left/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode;  // as new root TreeNode
}

// Same leftRotate's Rule will be followed for rightRotate with a minor change
// see leftRotate's comment for more clarity
TreeNode *rightRotate(TreeNode *parentNode) {
    TreeNode *medianNode = parentNode->left;
    TreeNode *T2 = medianNode->right;

// * perform rotation
    medianNode->right = parentNode;
    parentNode->left = T2;

// * Update Heights
    // first update parent TreeNode cuz it's on right/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode; // as new root
}

// Root, Left, Right
void PreOrderTraversal(TreeNode *root) {
    if (root) {
        cout << root->val << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

TreeNode *InsertInAVL(TreeNode *root, int val) {
    if (root == NULL)
        return new TreeNode(val);

    if (val < root->val)
        // Root node returned with val and height = 1
        root->left = InsertInAVL(root->left, val);
    else if (val > root->val)
        root->right = InsertInAVL(root->right, val);
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
    if (balance > 1 && val < root->left->val){
        root = rightRotate(root);
        return root;
    }

    // 2. handle right skewed unbalanced situation
//       X         Y
//        Y   to  X  Z  (Left Rotate)
//         Z
    if (balance < -1 && val > root->right->val) {
        root = leftRotate(root);
        return root;
    }
    // 3. handle Left, Right  unbalanced situation
//         X            X         Z
//       Y       to,   Z     to Y   X
//         Z.         Y
    if(balance > 1 && val > root->right->val){
        // first rotate root->left and it's child then root
        root->left = leftRotate(root->left);
        root = rightRotate(root);
        return root;
    }

    // 4. handle Right, left  unbalanced situation
//         X         X             Z
//           Y   to,   Z     to  X    Y
//         Z.            Y
    if(balance < -1 && val < root->right->val){
        // first rotate root->right and it's child then root
        root->right = rightRotate(root->right);
        root = leftRotate(root);
        return root;
    }

//  | ============================================ |
    return root;
}
void levelOrderTraversal(TreeNode *root) {
    queue<TreeNode *> q;
    q.push(root);
    q.push(NULL);
    cout<<"\n  ---------------------------\n";
    while (!q.empty()) {
        TreeNode *temp = q.front();
        q.pop();

        if (temp) {
            cout << temp->val << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
        // NULL will come after a complete level
        else { // if temp is NULL
            cout<<endl;
            if(!q.empty())
                q.push(NULL);
        }
    }
    cout<<"--------------------------------\n";
}

int main() {
    TreeNode *root = NULL;
    root = InsertInAVL(root, 12);
    root = InsertInAVL(root, 8);
    root = InsertInAVL(root, 4);
    cout<<"Printing PreOrder Traversal: \n";
    PreOrderTraversal(root); cout << endl;

    root = InsertInAVL(root, 6);
    root = InsertInAVL(root, 2);
    root = InsertInAVL(root, 3);
    root = InsertInAVL(root, 14);
    root = InsertInAVL(root, 16);
    cout<<"\nPrinting level Order Traversal: \n";
    levelOrderTraversal(root);
    
}
