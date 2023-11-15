#include "iostream"
#include "vector"
#include "queue"

using namespace std;

class AVL_Tree {
public:
    int val;
    AVL_Tree *left;
    AVL_Tree *right;
    int height;

    AVL_Tree(int val) {
        this->val = val;
        left = right = NULL;
        height = 1; // as new AVL_Tree is initially added at leaf
    }

};

int getHeight(AVL_Tree *node) {
    if (node == NULL)
        return 0;
    else
        return node->height;
}

// return the difference left & right node's height
int getBalance(AVL_Tree *node) {
    return getHeight(node->left) - getHeight(node->right);
}

// here in Function let
// T1 > T2 > ( parentNode > medianNode > leaf/updated AVL_Tree )
AVL_Tree *leftRotate(AVL_Tree *parentNode) {
    /*  Initial Example
     *      5 <- parentNode
     *     /  \
     *   (T1)  10  <- medianNode
     *         /  \
             (T2)  15 <- recently Inserted or updated AVL_Tree
             */

    AVL_Tree *medianNode = parentNode->right; // parentNode < medianNode < leftNode
    AVL_Tree *T2 = medianNode->left; // T2 > parentNode

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
    // first update parent AVL_Tree cuz it's on left/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode;  // as new root AVL_Tree
}

// Same leftRotate's Rule will be followed for rightRotate with a minor change
// see leftRotate's comment for more clarity
AVL_Tree *rightRotate(AVL_Tree *parentNode) {
    AVL_Tree *medianNode = parentNode->left;
    AVL_Tree *T2 = medianNode->right;

// * perform rotation
    medianNode->right = parentNode;
    parentNode->left = T2;

// * Update Heights
    // first update parent AVL_Tree cuz it's on right/below side of medianNode
    parentNode->height = 1 + std::max(
            getHeight(parentNode->left), getHeight(parentNode->right)
    );

    medianNode->height = 1 + std::max(
            getHeight(medianNode->left), getHeight(medianNode->right)
    );

    return medianNode; // as new root
}

// Root, Left, Right
void PreOrderTraversal(AVL_Tree *root) {
    if (root) {
        cout << root->val << " ";
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

AVL_Tree *InsertInAVL(AVL_Tree *root, int val) {
    if (root == NULL)
        return new AVL_Tree(val);

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
    if (balance > 1 && val < root->left->val) {
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
    if (balance > 1 && val > root->right->val) {
        // first rotate root->left and it's child then root
        root->left = leftRotate(root->left);
        root = rightRotate(root);
        return root;
    }

    // 4. handle Right, left  unbalanced situation
//         X         X             Z
//           Y   to,   Z     to  X    Y
//         Z.            Y
    if (balance < -1 && val < root->right->val) {
        // first rotate root->right and it's child then root
        root->right = rightRotate(root->right);
        root = leftRotate(root);
        return root;
    }

//  | ============================================ |
    return root;
}

AVL_Tree *deleteInAVL(AVL_Tree *root, int val) {
    if (root == NULL)
        return root;

    if (val < root->val)
        root->left = deleteInAVL(root->left, val);
    else if (val > root->val)
        root->right = deleteInAVL(root->right, val);
        // else val will match
    else {
        // Node with Only One Child or No Child
        if (root->right == NULL || root->left == NULL) {
            AVL_Tree *temp = root->left ? root->left : root->right; // whatever exist

            // no child Case
            if (temp == NULL) {
//                temp = root;
                root = NULL;
            } else {   // One child Case
                *root = *temp;  // copy the Values of that One Child
            }
            delete temp;    // as no longer required
        }
            // Node with Two Children Case
        else {
            AVL_Tree *inorderSuccessor = root->right;    // smallest on right side
            while (inorderSuccessor->left != NULL)
                inorderSuccessor = inorderSuccessor->left;

            root->val = inorderSuccessor->val;

            // Delete the inorder Successor, as it copied above
            root->right = deleteInAVL(root->right, inorderSuccessor->val);
        }

        // if leaf node was deleted
        if (root == NULL)
            return root;

        root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

        // get Balance factor as Node may Unbalance
        int balance = getBalance(root);

        // | ============================================ |
        //              ** Rotation Cases **

        // 1. handle left skewed unbalanced situation
//           X       Y
//          Y   to  Z X
//         Z
        if (balance > 1 && val < root->left->val) {
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
        if (balance > 1 && val > root->right->val) {
            // first rotate root->left and it's child then root
            root->left = leftRotate(root->left);
            root = rightRotate(root);
            return root;
        }

        // 4. handle Right, left  unbalanced situation
//         X         X             Z
//           Y   to,   Z     to  X    Y
//         Z.            Y
        if (balance < -1 && val < root->right->val) {
            // first rotate root->right and it's child then root
            root->right = rightRotate(root->right);
            root = leftRotate(root);
            return root;
        }

//  | ============================================ |
    }
    return root;
}

void levelOrderTraversal(AVL_Tree *root) {
    queue<AVL_Tree *> q;
    q.push(root);
    q.push(NULL);
    cout << "\n  ---------------------------\n";
    while (!q.empty()) {
        AVL_Tree *temp = q.front();
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
            cout << endl;
            if (!q.empty())
                q.push(NULL);
        }
    }
    cout << "--------------------------------\n";
}
