/*
Authors: Jason Toft and Chloe Guillemette
Purpose: Basic operations for the class of doubly linked list
Date: Feb 15, 2024
*/

#include <iostream>
using namespace std;
typedef int DataType;

struct Node {
    DataType data;
    Node *prev; // a pointer pointing to the previous node in the list
    Node *next;
    Node(int x) : data(x), prev(nullptr), next(nullptr) {};
};

class DoublyLinkedList{
    Node *head = nullptr;
    Node *tail = nullptr;   // a pointer pointing to the last node in the list
    int size;//, omitted

public:
    DoublyLinkedList(int x){
        size = x;
    }
    void insert(DataType value, int position);
    void replace(int position, DataType value);
    void remove(int position);
    Node* search(int target);// return a pointer to the target value
    void print(); // print all elements in the list
    void printReverse(); // print all elements in the list in reverse order
    //overload destructor, omitted
    //overload copy constructor, omitted
    //overload assignment operator =, omitted

};

void DoublyLinkedList::insert(DataType value, int position) {
    //step 1. check position validity, compare with 0 and size,
    //if not valid, quit, report error, or force into a valid value
    ////omitted in this demo, assuming it is valid
    if (position < 0 || position > size) {
        cerr << "Invalid position";
        return;
    }

    //step 2. create new node
    Node *newNode = new Node(value);

    //step 3. if special case, when position = 0
    //insert as the new head
    //3.1 when head == nullptr, or size == 0
    //the newNode will become the new head and the new tail
    //3.2 when size > 0, (position = 0)
    //insert at the head position
    //// actual code omitted
    if (position == 0) {
        if(head == nullptr || size == 0){
            // newNode points to nullptr
            newNode->next = nullptr;
            newNode->prev = nullptr;

            // head and tail are newNode
            head = newNode;
            tail = newNode;
            size ++;
            return;
        }
        else{ //3.2when size > 0
            //new node points to head
            newNode->next = head;
            // new node previous is nullptr
            newNode->prev = nullptr;
            // head previous points to new node
            head->prev = newNode;
            //new node is the new head
            head = newNode;
            size++;
            return;
        }
    }

    //step 4. when size > 0, position = size
    //insert at the end of the list, the node will become the new tail
    //// actual code omitted
    if (position == size && size > 0){
        // new node next points nowhere
        newNode->next = nullptr;
        // new node previous points to current tail
        newNode->prev = tail;
        //tail now points to new node
        tail->next = newNode;
        // tail becomes new node
        tail = newNode;
        size++;
        return;
    }

    //step 5. when size > 0, position > 0,  position < size
    //iterate through the list to find the position
    //with an additional pointer for the address of the previous node
    //may iterate from head to tail, in a way same as in singly linked list
    //may also iterate from tail to head.
    //alternatively, in a slightly improved version, may check if position is closer to head or tail,
    // then iterate from the closer end.
    //// actual code omitted
    //step 6. insert the node between previous and current (assume previous is closer to head)
    // properly link prev and next pointers
    //// actual code omitted
    if (size > 0 && position > 0 && position < size){
        int i;
        Node *current;
        if (position <= size/2){// closer to head
            Node *after;
            current->prev = nullptr; 
            current = head; // start at head
            current->next = head->next;
            i = 0;
            while (i < position-1){ // repeat until reaches the list node right before where the new node goes
                current = current->next;
                i++;
            }
            after = current-> next; // node that comes before new node
            newNode->prev = current; // current comes before new node
            newNode->next = after; //newnode comes before after
            current->next = newNode; // new node is after current
            after->prev = newNode; //new node is before "after"
        } else {
            Node *before;
            // current is tail (start at tail)
            current->prev = tail->prev;
            current = tail;
            current->next = nullptr;
            i = size;
            while (i > (size-position)){ // repeat until current is the node after the position of the new node
                current = current->prev;
                i--;
            }
            before = current->prev; // node before
            newNode->next = current; // new node points to current
            newNode->prev = before; // "before" is before new node
            before->next= newNode; // "before" points to new node
            current->prev = newNode; // current's previous points to new node
        }
    }
    size++;
}

void DoublyLinkedList::replace(int position, DataType value) {
    //may iterate from head to tail, in a way same as in singly linked list
    //may also iterate from tail to head.
    //alternatively, in a slightly improved version, may check if position is closer to head or tail,
    // then iterate from the closer end.

    //step 1. check position validity, compare with 0 and size,
    //if not valid, quit, report error, or force into a valid value
    ////omitted in this demo, assuming it is valid
    if (position > size || position < 0) { // invalid position
        cerr << "Invalid position";
        return;
    }

    //step 2. iterate a pointer to the position
    //// actual code omitted

    Node *current;
    Node *previousNode;
    Node *nextNode;
    Node *newNode = new Node(value);

    if (position == 0){ // base case
        current = head; // to be deleted later
        nextNode = head->next;
        if (size > 0){
            nextNode->prev = newNode;
            newNode->prev = nullptr;
            newNode->next = nextNode;
            head = newNode;
        } else { // new value is only value in the list
            current = head; // to be deleted later
            newNode->next = nullptr;
            newNode->prev = nullptr;
            head = newNode;
            tail = newNode;
        }
    } else {
    
        if (position <= size/2) {// start from head
            current = head;
            int i = 0;
            while (i != position){ // repeat until the node to be replaced is equal to current
                current = current->next;
                i++;
            }
        
        }  else { //start from tail
            current = tail;
            int i = size;
            while (i != (size-1-position)){ // repeat until the node to be replaced is equal to current
             current = current->prev;
             i--;
            }
        }

        //step 3. replace the value
        //// actual code omitted
        // make new nodes for simplicity
        previousNode = current->prev;
        nextNode = current->next;

        // newnode previous points to previos node
        newNode->prev = previousNode;

        //newnode next points to next node
        newNode->next = nextNode;

        // previous node's next points to new node
        previousNode->next = newNode;

        // next node's previous points to new node
        nextNode->prev = newNode;
    }
    // delete the replaced node
    current->prev = nullptr;
    current->next = nullptr;
    delete current;
        
}

void DoublyLinkedList::remove(int position) {
    //step 1. check position validity, compare with 0 and size,
    //if not valid, quit, report error, or force into a valid value
    ////omitted in this demo, assuming it is valid
    if (position > size || position < 0){
        cerr << "Invalid position";
        return;
    }

    //step 2.1 special case, if position == 0, remove head
    //if this is also the tail, properly set tail pointer
    //use a temp pointer
    //properly set the pointers, don't forget setting head pointer
    //deallocate node memory
    //// actual code omitted
    if(position == 0){ // base case
        if (tail == head){
            // Case where there is only one node
            Node *temp = tail;
            tail = nullptr;
            head = nullptr;
            delete temp;
            temp = nullptr;
        }
        else {
            // Case where there are multiple nodes
            Node *temphead = head;
            head = head->next;
            delete temphead;
            temphead = nullptr;
            head->prev = nullptr;
        }
        // Reduce the size of the linked list by 1 each time a node is removed
        size--;
        return;
    }

    //step 2.2, special case, if position == size - 1, remove tail
    //use a temp pointer
    //properly set the pointers, don't forget setting tail pointer
    //deallocate node memory
    //// actual code omitted

    // Removing the last node in the list
    if (position == size-1){
        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        size--;
        return;
    }

    //step 3. to prepare for removing a node in the middle of the list, find the pointer to the location
    //may iterate from head to tail, in a way same as in singly linked list
    //may also iterate from tail to head.
    //alternatively, in a slightly improved version, may check if position is closer to head or tail,
    // then iterate from the closer end.
    //// actual code omitted

    // Create two new nodes at and before the node being removed
    Node *current;
    Node *previous;
    
    // Iterate from the beginning of the list if the node being removed is in the first half
    if (position <= size/2){
        // Set the previous and current node pointers
        previous = head;
        current = head->next;

        int i = 1; // start iterating from the first position 
        while (i < position) {
            if (current->next == nullptr) {
                cerr << "There are not " << position << "members in the linked list. ";
                break; // reach the end
                //if this happens, it means that the position value is larger than it should be
                //by continuing the remaining code in this function,
                //the node at the tail of the list will be removed
            }
            // Shift the previous and current one node forward in the list
            previous = current;
            current = current->next;
            i++; // increment the index by one
        }

    // Iterate backwards from the end of the list if the node being removed is in the second half
    } else {
        // Set the previous and current node pointers
        previous = tail->prev;
        current = tail;

        int i = size-1; // Start indexing from the end of the list
        while (i > position) {
            if (previous->prev == nullptr) {
                cerr << "There are not " << position << "members in the linked list. ";
                break; // reach the end
                //if this happens, it means that the position value is larger than it should be
                //by continuing the remaining code in this function,
                //the node at the tail of the list will be removed

            }
            // Shift the previous and current one node backward in the list
            current = previous;
            previous = previous->prev;
            i--; // Move the index backward by one
        }
    }
    //step 4. after finding the proper pointers after iteration
    // remove the node and properly link the remaining nodes.
    //// actual code omitted
    previous->next = current->next;
    Node *nextnode = current->next;
    nextnode->prev = previous;
    current->next = nullptr;
    current->prev = nullptr;
    delete current;
    size--; // adjust the size of the linked list by subtracting 1 
    return;
}

Node* DoublyLinkedList::search(int target){
    // use a boolian variable to check if target is found or not
    // initially set it to false: bool found = false;
    // you can start searching from head or tail: current = head // current == tail

    // if target is found print a proper message and return a pointer to it.
    // if target is not in the linkedlist print a proper message and return nullptr as result.

    Node* currentfront = head; // current is the node that is being tested at the front 
    Node* currentback = tail; // current is the node that is being tested at the back
    int frontidx = 0; //index of front pointer
    int backidx = size-1; //index of back pointer
    int halfway = size/2; //halfway through list index
    bool found = false; // boolean keeping track of if the target value has been found in the list
    // if target is  not found and we have not completely searched the linked list
    while(!found && currentfront != nullptr && currentback != nullptr && frontidx<= halfway && backidx >= halfway){ // iterates through list until end or found the item
        if (currentfront->data == target) {
            cout << target << " is in the linked list" << endl; // outputs that the target was found
            found = true;
            return currentfront;
         }
        else if (currentback->data == target){
            cout << target << " is in the linked list" << endl; // outputs that the target was found
            found = true;
            return currentback;
        }  
        // move forward one for front pointer  
        currentfront = currentfront->next;
        frontidx++;

        // move backward one for back pointer
        currentback = currentback->prev;
        backidx--;
        
    }
    cout << target << " is not in the linked list" << endl; // outputs that the target was not found
    return nullptr; // return a null pointer when the target value is not in the list
}

void DoublyLinkedList::print() {
    if (head == nullptr) {
        return;
    }
    //print all nodes
    Node *temp = head;
    while (temp != nullptr) {
        cout<< temp->data << "->";
        temp = temp->next;
    }
    cout<< endl;
}

void DoublyLinkedList::printReverse() {
    if (tail == nullptr) {
        return;
    }
    //print all nodes in reverse order
    Node *temp = tail;
    while (temp != nullptr) {
        cout<< temp->data << "->";
        temp = temp->prev;
    }
    cout<< endl;
}


int main () {
    DoublyLinkedList myList (0);
    myList.insert(2, 0);
    myList.insert(4, 1);
    myList.insert(1, 0);
    myList.insert(5, 3);
    myList.insert(3, 2);

    myList.print();             //1->2->3->4->5->
    myList.printReverse();      //5->4->3->2->1->

    myList.remove(0);
    myList.remove(3);
    myList.remove(1);
    myList.print();             //2->4->
    myList.printReverse();      //4->2->
    
    // search the target value
    Node* target_ptr;
    target_ptr = myList.search(100);
    target_ptr = myList.search(1);

    return 0;
}