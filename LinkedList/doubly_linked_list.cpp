#include "iostream"
using namespace std;

class Node{
public:
    Node* prev;
    int data;
    Node* next;
    Node(int data){
        this->data = data;
    }
};

// insert at the front
void push(Node* &head,int d){

    Node* nodeToInsert = new Node(d);

    nodeToInsert->next = head;

    nodeToInsert->prev = NULL;

    if(head!=NULL)
        head->prev = nodeToInsert;
    // if list is already empty, we cannot perform NULL.prev to something

    // keep track of head pointer
    head = nodeToInsert;

}

// insert at end
void append(Node* &tail, int d){
    // if wrong pointer was passed by mistake
    if(tail->next != NULL)
        return;

    Node* nodeToInsert = new Node(d);

    tail->next = nodeToInsert;
    nodeToInsert->prev = tail;

    tail = nodeToInsert;    // update tail pointer to keep track of changes.
}

void InsertAtPosition(Node* &head,Node* &tail, int pos, int d){
    if(pos==1)  // insert at head
        push(head,d);

    // move the temp pointer, to where we have to insert new node
    Node* temp = head;
    int i = 1;
    while(i < pos -1 && temp!=NULL){
        temp = temp->next;
        i++;
    }
    if(temp == NULL){
        cout<<"!Out of bound position.\n";
        return;
    }
    // if temp is at last position, (at tail)
    if(temp->next == NULL){
        append(tail,d);     // we have to insert node after tail
        return;
    }

    Node* nodeToInsert = new Node(d);

    nodeToInsert->next = temp->next;
    nodeToInsert->prev = temp;

    temp->next->prev = nodeToInsert;
    temp->next = nodeToInsert;
}

void printList(Node* &head){
    Node* currTemp=head;
    while(currTemp!=NULL){
        cout<<currTemp->data<<" ";
        currTemp = currTemp->next;
    }
    cout<<endl;
}

int main(){

    Node* node1 = new Node(5);
    // initializing head and tail
    Node* head = node1;
    Node* tail = node1;

    // * Insertion
    push(head,7);   // 7 5
    InsertAtPosition(head,tail,3,8);     // 7 5 8
    append(tail,3);         // 7 5 8 3
    InsertAtPosition(head,tail,2,10);    // 7 10 5 8 3

    printList(head);
}
