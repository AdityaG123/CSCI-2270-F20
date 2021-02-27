#include <iostream> // predefined header file (defined for you)
#include <string>
using namespace std;

#include "SLL.hpp" // your own header file
// <> vs "" -- compiler looks for the file in the C++ implementation
// vs in the current directory


SLL::SLL(){ // constructor definition
	headOne = nullptr;
	headTwo = nullptr;
}

SLL::SLL(string demo)
{
	headOne = nullptr;
	headTwo = nullptr;
	if (demo == "demo")
	{
		string def[]= {"che","the","fluffy","cat"};
		insert(nullptr, def[0]);
		for(int i=1;i<4;i++)
		{
				Node* prev = search(def[i-1]);
				insert(prev, def[i]);
		}
	}
	else{
		insert(nullptr, demo);
	}
}

SLL::~SLL(){
    //TODO
    Node *temp = new Node;
    Node *temp1 = new Node;
    while(headOne != nullptr){  
        temp = headOne;   //from lecture slides
        temp = headOne->next;
        delete headOne;
        headOne = temp;
    }
    delete headOne;
    
    while (headTwo != nullptr){
        temp1 = headTwo;    //from lecture slides
        temp1 = headTwo->next;
        delete headTwo;
        headTwo = temp1;
    }
    delete headTwo;
    
}

Node* SLL::search(string sKey){

    Node* crawler = headOne;

    while( crawler != nullptr && crawler->key != sKey){
        crawler = crawler->next;
    }

    return crawler;

}

void SLL::displayList(){
    Node* crawler = headOne;
    cout<< "LL1:";
    while( crawler != nullptr ){
        cout << crawler->key << "->";
        crawler = crawler->next;
    }
    cout << "END" << endl;

    crawler = headTwo;
    cout<< "LL2:";
    while( crawler != nullptr ){
        cout << crawler->key << "->";
        crawler = crawler->next;
    }
    cout << "END" << endl;
}


void SLL::insert(Node* afterMe, string newValue){

    if(headOne == nullptr){
        // first case: empty list
        // add new node and make headOne point to it
        headOne = new Node;
        headOne->key = newValue;
        headOne->next = nullptr; // what if we forget this line?
    }
    else if(afterMe == nullptr){
        // This condition implies that the list is not empty, but
        // the caller wants to add node before the headOne node
        Node* newNode = new Node;
        newNode->key = newValue;
        newNode->next = headOne;
        headOne = newNode;
        // at this point, we can test our code for this use case

    }
    else{
        Node* newNode = new Node;
        newNode->key = newValue;
        newNode->next = afterMe->next;
        afterMe->next = newNode;
    }


}

void SLL::deleteNode(string sKey)
{
    Node *deleteNode = search(sKey);
    if( deleteNode != nullptr)
    {
        // check if deleteNode is headOne
        if( deleteNode == headOne ){
            headOne = headOne->next;
            delete deleteNode;
        }
        //traverse the list:
        else
        {
            Node* crawler = headOne;
            // Stop at node prior the node to be deleted
            while(crawler->next != deleteNode){
                crawler = crawler->next;
            }

            // reconnect the LL around the node about to
            // be removed
            crawler->next = crawler->next->next;

            // deallocate
            delete deleteNode;
        }

    }
    else{
        cout << "Node doesn't exist. Nothing to do." << endl;
    }
}

int SLL::split(string searchKey)
{
    //TODO  
    Node *temp;
    Node *previous; 
    if(headTwo != nullptr){
        return 2;
    }
    else{
        temp = headOne;
        
        while(temp != nullptr){
            while(temp->key != searchKey){
                previous = temp;
                temp = temp->next;
            }
        }

        // for(temp = nullptr; temp != nullptr; temp = temp->next){
        //     for(temp->key; temp->key != searchKey; temp = temp->next){
        //         prev = temp;
        //     }
        // }
        if(temp->next = nullptr){
            if(temp->key != searchKey){
                return 1;
            }
            else{
                return 0;
            }
        }
        else if(temp->key == searchKey){
            headOne->next = headTwo;
            headOne = temp;
            headOne = nullptr;
            temp->next = nullptr;
            headTwo = headOne->next;
        }
        else{
            previous->next = nullptr;
            headTwo->next = nullptr;
            return 0;
        }
    }

    return 0;
}

//keeps not splitting the LL and I dont know why
