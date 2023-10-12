#include "iostream"
#include "queue"
using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

Node* buildFromLevel(Node* &root){
    queue<Node*> q;
    cout<<"Enter data for root > ";
    int rootData;
    cin>>rootData;
    root = new Node(rootData);
    q.push(root);

    while(!q.empty()){
        Node* temp = q.front();
        q.pop();

        // Enter Data on left of Node
        cout << "Enter left node for  " << temp->data << " > ";
        int leftData;
        cin >> leftData;

        if(leftData != -1) {
            temp -> left = new Node(leftData);
            q.push(temp->left);
        }

        // Enter Data on right of Node
        cout << "Enter right node for " << temp->data << " > ";
        int rightData;
        cin >> rightData;

        if(leftData != -1) {
            temp -> right = new Node(rightData);
            q.push(temp->right);
        }
    }
    return root;
}

Node *buildTree(Node *root) {
    cout << "\tEnter the data > ";
    int data;
    cin >> data;
    root = new Node(data);

    if (data == -1)
        return NULL;
    cout << "Left of " << data << endl;
    root->left = buildTree(root->left);

    cout << "Right of " << data << endl;
    root->right = buildTree(root->right);

    return root;
}

void levelOrderTraversal(Node *root) {
    queue<Node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();

        if (temp) {
            cout << temp->data << " ";
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
}

// (left, right, root)
void postorder(Node *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}



int main() {

    Node *root = NULL;
    root = buildFromLevel(root);
    cout<<endl;
    levelOrderTraversal(root);


}
