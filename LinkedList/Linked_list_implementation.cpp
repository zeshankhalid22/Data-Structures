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

void deleteAtPosition(Node* &head, Node* &tail, int pos){
    if(pos<1){
        cout<<"! Out Of Bound Position.\n";
        return;
    }
    // Only for 1st Position
    if(pos==1){
        Node* temp = head;
        head = head->Next;
        if(temp==tail)
            tail = head;    // Update the tail pointer if last element is being deleted.
        delete temp;
        return;
    }
    int cnt = 1;
    Node* prev = head;
    while(cnt<pos-1){
        if(prev==NULL){
            cout<<"! Out Of Bound Position.\n";
            return;
        }
        prev = prev->Next;
        cnt++;
    }
    Node* curr = prev->Next;
    prev->Next = curr->Next;
    if(prev->Next==NULL)    // if prev is last element, then update its address to tail object
        tail = prev;
    delete curr;
}

void deleteByValue(Node* &head,Node* &tail,int targetValue){
    int pos = 1;    //  I will start comparing at 1st position
    Node* currNode = head;
    while(currNode!=NULL){
        int db = currNode->data;
        if(currNode->data == targetValue){

            currNode = currNode->Next;
            // if we don't update currNode above, then After running below, Location of currNode will be deleted(free).
            // and now currNode is pointing to dangling pointer
            deleteAtPosition(head,tail,pos);

//            return;   // Comment return , if you want to DELETE all values=targetValue

        }
        else{
            currNode = currNode->Next;
            pos++;
        }
    }
}

void FindMiddle(Node* &head){

    if(head == NULL){
        cout<<"! No Middle Value "<<endl;
    }

    Node* temp = head;
    Node* middle = head;
    while(true){
        if(temp==NULL || temp->Next==NULL){
            cout<<"Middle Value: "<< middle->data<<endl;
            return;
        }
        temp = temp->Next->Next;
        middle = middle->Next;
    }
}

void reverseList(Node* &head,Node* &tail) {
    if(head == NULL || head->Next == NULL)
        return;

    Node* prev = NULL;
    Node* curr = head;
    Node* forward = NULL;
    while(curr!=NULL){
        forward = curr->Next;    // Store the remaining list address
        curr->Next = prev;  // Reverse the address
        // Move Address 1 step ahead
        prev = curr;
        curr = forward;
    }
    tail = head;
    head = prev;
}

void printListRecursion(Node* temp) {

    if (temp == NULL)  // Base condition
        return;

//    cout<<temp->data<<" ";  // Print in Original order -> tail recursion
    printListRecursion(temp->Next);
    cout<<temp->data<<" ";      // print in reverse order: -> head recursion
}

Node* reverseKgroups(Node* head, int k){
    Node* current = head;
    Node* prev = NULL;
    Node* forward = NULL;
    int count = 0;

    while(count < k && current != NULL){
        forward = current->Next;
        current->Next = prev;

        prev = current;
        current = forward;
        count++;
    }
    // it means we couldn't perform enough operations (count < k)
    if(count!=k)
        return head;    // return the first element without reversing
        //  {1 3 4, [5 6]}, k=3, return 5(which was head here)

    head->Next = reverseKgroups(forward, k);
    return prev;
}

Node* updateTail(Node* head) {
    Node* temp = head;
    while (temp->Next != NULL) {
        temp = temp->Next;
    }
    return temp;
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

//    printLinkedlist(head);      cout<<endl;

    InsertAtmiddle(head,tail,2,10);  // 10, *10, 77, 15, 25
    InsertAtmiddle(head,tail,3,66);  // 10, 10, 66*, 77, 15, 25
//    InsertAtmiddle(head,tail,100,66); // Out of Bound Position, 66 Inserted at Last

    // as num1 list is going to be reversed/changed, head(main) will be pointing to old head location,
    // which may changed(centered/moved) during reverse operations, tail will also,
    head = reverseKgroups(head, 3);  // ! work here
    printLinkedlist(head);
    updateTail(head);   // update tail to very last element after reversing/changing list



////    printListRecursion(head);
//    printLinkedlist(head);      cout<<endl;
//
//    deleteAtPosition(head,tail,6);      // 10, 10, 66, 77, 15, *
//    deleteAtPosition(head, tail, 4);    // 10, 10, 66, 77*, 15
//
//    printLinkedlist(head);  cout<<endl; // 10, 10, 66, 15
//
//    reverseList(head,tail);         // 15, 66, 10, 10
//    printLinkedlist(head);
//
//    deleteByValue(head,tail,10);    // 10*, 10*, 66, 15
//    deleteByValue(head,tail,15);    // 66 15*
//
//    printLinkedlist(head);  cout<<endl; // 66j


}
