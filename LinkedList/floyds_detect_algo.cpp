#include "iostream"
using namespace std;

class Node{
public:
    int data;
    Node *Next;
    Node(int data){
        this->data = data;
        this->Next = NULL;
    }

};

void InsertAtfront(Node* &head,Node* &NewNode){
NewNode->Next = head;
head = NewNode;
}

void InsertAtEnd(Node* &tail, int d){
    Node* end = new Node(d);
    tail->Next = end;
    tail = end;
}

void InsertAtmiddle(Node* &head,Node* &tail,int pos,int val){
    if(pos==1){
        Node* someNode = new Node(val);
        InsertAtfront(head,someNode);
        return;
    }
        Node* currTemp = head;
        Node* NewNode = new Node(val);
    for(int i=1;i<pos-1;i++){
        if(currTemp->Next==NULL){   // If position is going out of Index, then Insert the value at Last pos
            InsertAtEnd(tail,val);
            return;
        }
        currTemp = currTemp->Next;
    }
    NewNode->Next = currTemp->Next;
    currTemp->Next = NewNode;

}

void printLinkedlist(Node* &head){
    Node* currTemp=head;
    while(currTemp!=NULL){
        cout<<currTemp->data<<" ";
        currTemp = currTemp->Next;
    }
    cout<<endl;
}

Node* FloydsDetect(Node* head){
    if(head==NULL)
        return NULL;

    Node* fast = head;
    Node* slow = head;

    while(slow!=NULL && fast!=NULL){
        // fast pointer will move 2 step at a time, while slow will move only 1 step
        fast = fast->Next;
        if(fast!=NULL)
            fast = fast->Next;

        slow = slow->Next;

        if(slow == fast)
            return slow;
    }
    return NULL;

}

Node* getStartingNodeOfLoop(Node* head){
    if(head == NULL)    // emptry linked list
        return NULL;

    Node* intersect = FloydsDetect(head);

    if(intersect==NULL)     // no loop exist
        return NULL;

    Node* slow = head;

    while(slow!=intersect){
        slow = slow->Next;
        intersect = intersect->Next;
    }

    return slow;    // or intersect
}

Node* removeLoop(Node* head){
    if(head == NULL)    // emptry linked list
        return NULL;

    Node* intersect = FloydsDetect(head);

    if(intersect==NULL)     // no loop exist
        return NULL;

    Node* slow = head;

    while(slow!=intersect){
        slow = slow->Next;
        if(intersect->Next==slow){  // exactly 1 Node before both pointers meets at starting position
        intersect->Next = NULL;
        break;
        }
        intersect = intersect->Next;
    }
     return head;
}

int main(){
    // Change will be represented with *

    Node*  node1 = new Node(77);    // 77
    Node* head= node1;
    Node* tail = node1;
   Node* newNode = new Node(10);

    InsertAtfront(head,newNode);    // 10* 77

    InsertAtEnd(tail,15);   // 10, 77, 15
    InsertAtEnd(tail,25);   // 10, 77, 15, 25*


    InsertAtmiddle(head,tail,2,17);  // 10, *10, 77, 15, 25
    InsertAtmiddle(head,tail,3,66);  // 10, 10, 66*, 77, 15, 25
    printLinkedlist(head);

    // Now Node(25) will point to Node(66)
    tail->Next = head->Next->Next;

    Node* temp = FloydsDetect(head);
    if(temp==NULL)
        cout<<"No loop found.\n";
    else
        cout<<"loop detected.\n";

    temp = getStartingNodeOfLoop(head);
    if(temp!=NULL)
        cout<<"loop started at "<<temp->data<<" Value.\n";

    temp = removeLoop(head);
    if(temp!=NULL)
        cout<<"loop removed.\n";
    
}

