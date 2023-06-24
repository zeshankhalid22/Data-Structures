#include "iostream"
using namespace std;
#include "unordered_set"

class Node{
public:
    int data;
    Node *Next;
    Node(int data){
        this->data = data;
        this->Next = NULL;
    }

};

void InsertAtEnd(Node* &tail, int d){
    Node* end = new Node(d);
    tail->Next = end;
    tail = end;
}

void printLinkedlist(Node* &head){
    Node* currTemp=head;
    while(currTemp!=NULL){
        cout<<currTemp->data<<" ";
        currTemp = currTemp->Next;
    }
    cout<<endl;
}


void Sort_012_count_frequency(Node* head){
    int count[3]={0,0,0};

    Node* temp = head;

    while(temp!=NULL){  // count how many 0,1 and 2's
        // ! Linked list data must be between 0-2
        count[temp->data] += 1;    // Count[0 || 1 || 2] += 1
        temp = temp->Next;
    }

    // Now fill the data according to count respectively
    temp = head;

    // Fill 0's
    for(int i=0;i<count[0];i++){
        temp->data = 0;
        temp = temp->Next;
    }

    // Fill 1's
    for(int i=0;i<count[1];i++){
        temp->data = 1;
        temp = temp->Next;
    }

    // Fill 2's
    for(int i=0;i<count[2];i++){
        temp->data = 2;
        temp = temp->Next;
    }
}

void Sort_012_changing_links(Node* &head){

    if(head==NULL || head->Next==NULL)
        return;
    // three pointer pointing to Heads of three linked lists
    Node* zeroH = new Node(-1);
    Node* oneH = new Node(-1);
    Node* twoH = new Node(-1);

    // pointer that will maintain tail
    Node* zero = zeroH;
    Node* one = oneH;
    Node* two = twoH;

    Node* curr = head;  // pointer to traverse list
    while(curr != NULL){
        if(curr->data == 0){
            zero->Next = curr;
            zero = zero->Next;
        }
        else if(curr->data == 1){
            one->Next = curr;
            one = one->Next;
        }
        else if(curr->data == 2){
            two->Next = curr;
            two = two->Next;
        }
        curr = curr->Next;
    }

    if(oneH->Next==NULL){   // if 1 (one) list is emtpy
        zero->Next = twoH->Next;
    }
    else{
        zero->Next = oneH->Next;
        one->Next = twoH->Next;
    }

    two->Next = NULL;   // end of linked list

    head = zeroH->Next; // update head

    delete oneH, twoH, zeroH;

}
int main(){
    // Change will be represented with *

    Node*  node1 = new Node(1);
    Node* head= node1;
    Node* tail = node1;


    InsertAtEnd(tail,2);
    InsertAtEnd(tail,0);
    InsertAtEnd(tail,1);
    InsertAtEnd(tail,2);
    InsertAtEnd(tail,0);
    InsertAtEnd(tail,0);
    InsertAtEnd(tail,1);
    InsertAtEnd(tail,1);


    printLinkedlist(head);

//    Sort_012_count_frequency(head);
    Sort_012_changing_links(head);
    printLinkedlist(head);





}

