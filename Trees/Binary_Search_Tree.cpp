#include "iostream"
#include "queue"

using namespace std;

class BST {
public:
    int data;
    BST *left;
    BST *right;

    BST(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }


};

BST *insertIntoBst(BST *root, int d) {
    // base case
    if (root == NULL) {
        return new BST(d);
    }

    if (d < root->data) {
        root->left = insertIntoBst(root->left, d);
    } else {
        root->right = insertIntoBst(root->right, d);
    }
    return root;
}

// function to take input and insert into BST
void BuildTree(BST *&root) {
    cout << "\tEnter the data > ";
    int data;
    cin >> data;
    while (data != -1) {
        root = insertIntoBst(root, data);
        cout << "\t > ";
        cin >> data;
    }


}

void levelOrderTraversal(BST *root) {
    queue<BST *> q;
    q.push(root);
    q.push(NULL);
    cout << "Printing level order traversal of BST: \n";
    // temp will always contain front of queue, and will be used
    // to insert its child nodes in queue
    while (!q.empty()) {
        BST *temp = q.front();
        q.pop();

        if (temp) {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
            // if temp==NULL, means are at end of level
        else {
            cout << endl;
            if (!q.empty())
                q.push(NULL);
        }
    }
}

// inOrder traversal of BST gives sorted order by default
void inOrder(BST *root) {
    if (root == NULL) {
        cout << endl;
        return;
    }
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

//       average worst
// T.C =  O(H)   O(n)
// S.C =  O(H)   O(n)
bool searchBST(BST *root, int target) {
    BST *temp = root;

    while (temp != NULL) {
        if (temp->data == target) {
            return true;
        } else if (temp->data > target) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    // if loop is completed, means element not found
    return false;
}

BST *inOrderSuccessor(BST *root, int value) {
    BST *Successor = NULL;
    BST *temp = root;
    while (temp != NULL) {
        if (value > temp->data) {
            temp = temp->right;
        } else if (value < temp->data) {
            Successor = temp;
            temp = temp->left;
        } else {
            return Successor;
        }
    }

    return Successor;
}

BST *getMinVal(BST* root){
    BST* temp = root;
    // keep traversing the left side till leaf node
    while(temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

BST* deleteFromBST(BST* root, int val){
    // base case
    if(root==NULL)
        return NULL;

    // if value found, perform deletion
    if(root->data==val){
        // 0 child case, leaf node
        if(root->left==NULL && root->right==NULL){
            delete root;
            return NULL;
        }

        // 1 child case
            //1.1 left child
        if(root->left!=NULL && root->right==NULL){
            BST* curr = root->left;
            delete root;
            return curr;
            // return root->left;   // just 1 line way
        }
            //1.2 right child
        if(root->left==NULL && root->right!=NULL){
            BST* temp = root->right;
            delete root;
            return temp;
            // return root->right;   // just 1 line way
        }

        // 2 child case
        // * Choose 1 Method only
            // 2.1 choose maximum value from left subtree
            // not implementing.

            // 2.2 choose minimum value from right subtree
            // * Why it works?
            // bcz min value of right subTree will be greater than from left subtree
            // and if I insert (minVal at curr), right subtree will always greater
        BST* minVal = getMinVal(root->right);
        root->data = minVal->data;  // copy minVal to currNode
        // minVal's Node should be deleted, cuz it's values is copied here into curr
        root->right = deleteFromBST(root->right, minVal->data);
        return root;


    }
    // go left and match again
    if(val < root->data){
        root->left = deleteFromBST(root->left, val);
        return root;
    }
    // go right and match
    else{
        root->right = deleteFromBST(root->right, val);
        return root;
    }
}

int main() {
    BST *root = NULL;
    BuildTree(root);
    levelOrderTraversal(root);

    // * Searching in BST
   int val;
   cout<<"Enter value to search in BST: ";
   cin>>val;
   cout<<"Searching "<<val<<" in BST: ";
    if(searchBST(root, val))
         cout<<"Found\n";
    else
         cout<<"Not Found\n";

    // * find inOrder successor of a value
     cout<<"Enter value to find it's successor: ";
     cin>>val;
     BST* Successor = inOrderSuccessor(root, val);
     if(Successor)
        cout<<"Successor of "<<val<<" is "<<Successor->data<<endl;
     else
         cout<<"Successor not found\n";

     // * delete a node from BST
    cout<<"Enter value to delete from BST: ";
    cin>>val;
    cout<<"Deleting "<<val<<" from BST: ";
    root = deleteFromBST(root,val);
    cout<<endl;
    levelOrderTraversal(root);
}
