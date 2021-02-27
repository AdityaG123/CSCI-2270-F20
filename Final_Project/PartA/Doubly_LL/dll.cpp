#include "dll.hpp"
#include <iostream>
using namespace std;


//constructor that sets the head of the linked list to null
DoublyLinkedList::DoublyLinkedList(){
    head = nullptr;
}


//initializes the nodes in the double linked list
Node * DoublyLinkedList::createNode(int key){
    Node * newNode = new Node;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    newNode->key = key;
    return newNode;
}

Node * DoublyLinkedList::searchNodes(int key){
    Node * search = head;                           //creates a new node pointer
    while(search != nullptr){                       //if the head is a nullptr, then it creates a new head
        if(search->key == key){
            return search;                          //if the head has a key, then it returns the search head.
        }
        search = search->next;                      //increments the next search pointer
    }
    return nullptr;
}

void DoublyLinkedList::addNode(int key){
    Node * addNode = createNode(key);               //adds new node pointer in linked list
    addNode->prev = nullptr;                        //sets the previos node to null
    addNode->next = head;                           // sets new head at next node pointer
    if(head != nullptr){                            //if the head is a nullptr in the LL then add a node before the current node and set as the head.
        head->prev = addNode;
    }
    head = addNode;                                 //inserts a new node as head.
    return;
}

void DoublyLinkedList::printNodes(){
    Node * printNode = head;                
    while(printNode != nullptr){                    //goes through the entire LL and prints the node's key value for each node
        cout << printNode->key << ", " << endl;
        printNode = printNode->next;                //moves and prints next node key
    }
}