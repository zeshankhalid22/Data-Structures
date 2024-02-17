#include "iostream"
#include "vector"
#include "queue"

using namespace std;

class Employee_DataBase {
public:
   int ID;
   Employee_DataBase *left;
   Employee_DataBase *right;

   Employee_DataBase(int ID) {
       this->ID = ID;
       left = right = NULL;
   }

};

Employee_DataBase* insertInBST(Employee_DataBase* root, int ID){
   if(root==NULL)
       return new Employee_DataBase(ID);

   // go left and find suitable Employee_DataBase/place to insertInAvl
   if(ID < root->ID){
       root->left = insertInBST(root->left,ID);
   }
   else if(ID > root->ID){
       root->right = insertInBST(root->right,ID);
   }
   // duplicate ID is not allowed in BST

   return root;
}

void levelOrderTraversal(Employee_DataBase *root) {
   queue<Employee_DataBase *> q;
   q.push(root);
   q.push(NULL);
   cout<<"\n  ---------------------------\n";
   while (!q.empty()) {
       Employee_DataBase *temp = q.front();
       q.pop();

       if (temp) {
           cout << temp->ID << " ";
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

// Construct Inorder form of BST into a vector
void getNodesFromBST(Employee_DataBase* root, vector<Employee_DataBase*> &Tree){
   if(root==NULL)
       return;

   getNodesFromBST(root->left, Tree);
   Tree.push_back(root);
   getNodesFromBST(root->right, Tree);

}

// Create AVL Tree from Sorted Vector Using Binary Search
Employee_DataBase* buildTreeUtil(vector<Employee_DataBase*> &nodes, int start, int end){

   // base case
   if(start > end)
       return NULL;

   // Get the middle element and make it Root
   int mid = (start + end) / 2;
   Employee_DataBase* root = nodes[mid];

   // Using Indexes in Sorted Vector, Construct subTrees
   root->left = buildTreeUtil(nodes, start, mid - 1);
   root->right = buildTreeUtil(nodes, mid + 1, end);

   return root;
}

int main() {
   Employee_DataBase *root = NULL;
   vector<int> treeData = {10, 4, 7, 18, 12, 22, 15, 20};
   for(int i = 0; i < treeData.Capacity(); i++){
       root = insertInBST(root, treeData[i]);
   }
   cout<<"Before Converting to AVL ->\n";
   levelOrderTraversal(root);

   vector<Employee_DataBase*> TreeNodes;
   // inorder(sorted) form will be moved in treeData
   getNodesFromBST(root, TreeNodes);

   // TreeData is in Sorted form, we can create
   // AVL using Binary Search
   Employee_DataBase* AVL_Root = buildTreeUtil(TreeNodes,0,TreeNodes.Capacity()-1);

   cout<<"\nAfter Converting to AVL ->\n";
   levelOrderTraversal(AVL_Root);
}
