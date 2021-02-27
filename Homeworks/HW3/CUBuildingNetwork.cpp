/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */

bool append(string* &str_arr, string s, int &numEntries, int &arraySize)
{
    if(numEntries<arraySize){
       str_arr[numEntries] = s;
       numEntries++;
       return false;
   }
   else{
       string * newArray = new string[arraySize*2];
       //copy existing values
       for(int i=0;i<arraySize;i++){
           newArray[i] = str_arr[i];
       }
       arraySize *=2;
       newArray[numEntries] = s;
       str_arr = newArray;
       numEntries++;
       return true;
   }

}

CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom)
{
    CUBuilding *node = new CUBuilding;

    if(head == NULL){//if there's nothing in the LL 
        node->name=buildingName; //set building name
        node->totalRoom = numOfroom; //set num of rooms
        node->next = NULL; //point the node
        head = node; //update the head    
        cout << "adding: " << buildingName << " (HEAD)" << endl;
    }

    else if(head->next== NULL){ //case 1 we're at the beginning of the LL
        node->totalRoom = numOfroom;
        node->name = buildingName;
        head->next = node;
        node->next = NULL;
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    }

    else if(previous == NULL){ //case 3 we want to insert in the very beginning of a LL
        node->totalRoom = numOfroom;
        node->name = buildingName;
        node->next = head;
        head = node;
        cout << "adding: " << buildingName << " (HEAD)"<<endl;
    }

    else { //inserting in between nodes
        node->totalRoom = numOfroom;
        node->name = buildingName;
        node->next = previous->next; //our node points to the same place as the previous
        previous->next= node; //the previous now points to our node
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
    }

    
}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    addBuildingInfo(nullptr, "FLMG", 2);
    addBuildingInfo(searchForBuilding("FLMG"), "DLC", 10);
    addBuildingInfo(searchForBuilding("DLC"), "ECOT", 6);
    addBuildingInfo(searchForBuilding("ECOT"), "CASE", 5);
    addBuildingInfo(searchForBuilding("CASE"), "AERO", 4);
    addBuildingInfo(searchForBuilding("AERO"), "RGNT", 9);
    searchForBuilding("RGNT")->next = nullptr;  
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    CUBuilding * ptr = head;
    while (ptr != NULL && ptr->name != buildingName){
        ptr = ptr->next;
    }
  return ptr;
}


/*
 * Purpose:
 * @param string receiver
 * @param string msg
 */

void CUBuildingNetwork::transmitRoomInfo(string receiver)
{
    string message;
    int totalRoom;
    if (head == NULL) {
        cout << "Empty list" << endl;
    } 
    else if (searchForBuilding(receiver) == NULL) {
        cout << "Building not found" << endl;
    } 
    else {
        CUBuilding* node = head;
        while (true) {
            node->message = message;
            node->numberMessages++;
            cout << node->name << " [# messages received: " << node->numberMessages << "] received: available room at " << node->name << " is " << node->totalRoom << endl;
            if (node->name == receiver) {
                break;
            }
        node = node->next;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    CUBuilding* temp = head;
    cout << "== CURRENT PATH ==" << endl;
    if (head == NULL) {
        cout << "nothing in path" << endl;
    } 
    else {
        while(temp->next != NULL){
        cout<< temp->name <<"(" << temp->totalRoom << ") -> ";
        temp = temp->next;
        }
        cout <<temp->name<< "(" << temp->totalRoom <<") -> "<<"NULL"<< endl;
    }
    cout << "===" << endl;
}

//main for the bool append function for array doubl
// int main(){
//     string * myArray;
//    int arraySize = 2;
//    myArray = new string[2];
//    int numEntries = 0;
//    append(myArray,"one",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"two",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"three",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"four",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"five",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"six",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;
//    append(myArray,"seven",numEntries,arraySize);
//    cout<<"Array size is : "<<arraySize<<" ; Current array index is : "<<numEntries<<endl;

//    for(int i=0;i<numEntries;i++){
//        cout<<myArray[i]<<endl;
//    }
//    return 0;
// }