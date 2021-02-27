/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of Building structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
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
 * Purpose: Add a new building to the network between the building *previous and the building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    // if we are passed an empty list, just create a new head node, and return

    if (head == NULL)
    {
        cout << "adding: " << buildingName << " (HEAD)" << endl;
        head = new CUBuilding;
        head->name = buildingName;
        head->numberMessages = 0;
        head->totalRoom = numOfroom;

        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        cout << "adding: " <<buildingName<< " (HEAD)" << endl;
        CUBuilding *c = new CUBuilding;
        c->name = buildingName;
        c->numberMessages = 0;
        c->next = head;
        c->totalRoom = numOfroom;

        head = c;
    }else{
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
        CUBuilding *newBuilding = new CUBuilding;
        newBuilding->name = buildingName;
        newBuilding->numberMessages = 0;
        newBuilding->next = previous->next;
        newBuilding->totalRoom = numOfroom;

        previous->next = newBuilding;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    int num_buildings = 6;
    string buildings[] = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int rooms[] = {2,10,6,5,4,9};
    head = NULL;
    CUBuilding* prev = NULL;
    for(int i = 0; i < num_buildings; i++)
    {
        addBuildingInfo(prev, buildings[i],rooms[i]);
        prev = searchForBuilding(buildings[i]);
    }
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // Search until the head is NULL, or we find the building
    CUBuilding* ptr = head;
    while (ptr != NULL && ptr->name != buildingName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    CUBuilding* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr != NULL)
        {
            cout << ptr->name << "(" << ptr->totalRoom << ")" <<" -> ";
            ptr = ptr->next;
        }
        //cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
  }

/*
 * Purpose: delete the building in the network with the specified name.
 * @param buildingName name of the building to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) {
    //TODO: Complete this function
    if (searchForBuilding(buildingName) == NULL) {
        cout << "Building does not exist." << endl;
    } 
    else {
        CUBuilding* temp = head;
        CUBuilding* prev = NULL;
        if (head->name == buildingName) {
            CUBuilding* newNode = head;
            head = head->next;
            delete newNode;
        } 
        else {
            while (temp->name != buildingName) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            delete temp;
        }
    }
}

/*
* Purpose: Creates a loop from last node to the building specified.
* @param buildingName name of the building to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) {
    //TODO: Complete this function
    CUBuilding *temp = head;
    CUBuilding *target = NULL;
    CUBuilding *last;
    while (temp != NULL){
        if (temp->name == buildingName){
            target = temp;
        }
        last = temp;
        temp = temp->next;
    }
    if (target != NULL){
        last->next = target;
    }
    return last;
}

/*
 * Purpose: deletes all buildings in the network starting at the head building.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    //TODO: Complete this function
    CUBuilding* node = head;
    while (node != NULL) {
        cout << "deleting: " << node->name << endl;
        delete node;
        node = node->next;
    }
    head = NULL;
    cout << "Deleted network" << endl;
}

/*
 * Purpose: to detect loop in the linkedlist
 * @return: true if loop is detected.
 */
bool CUBuildingNetwork::detectLoop() {
    //TODO: Complete this function
    CUBuilding *start = head;
    CUBuilding *temp = head->next;
    while (start != NULL && temp != NULL && temp->next != NULL){
        start = start->next;
        temp = temp->next->next;
        if (start == temp){
            return true;
        }
    }
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 * @param: start index, end index
 * @return: none
 */
void CUBuildingNetwork:: readjustNetwork(int start_index, int end_index)
{
    //TODO: Complete this function
    if(head == NULL){
        cout << "Linked List is Empty" << endl;
        return;
    }
    CUBuilding * cur = head;
    int len = 0;
    while(cur != NULL){
        len++;
        cur = cur->next;
    }
    if(end_index < 0 || end_index >= len - 1){
        cout << "Invalid end index" << endl;
        return;
    }
    if(start_index < 0 || start_index > len){
        cout << "Invalid end index" << endl;
        return;
    }
    if(start_index > end_index){
        cout << "Invalid indices" << endl;
        return;
    }
    int building = 0;
    CUBuilding* current = head;
    CUBuilding* prev = NULL;
    CUBuilding* p;
    CUBuilding* c;
    CUBuilding* l;
    while(current != NULL){
        if(building == start_index){
            p = prev;
            c = current;
        }
        if(building == end_index){
            l = current;
        }
        prev = current;
        current = current->next;
        building++;
    }
    prev->next = c;
    CUBuilding* temp = l->next;
    l->next = NULL;
    if(start_index == 0){
        head = temp;
    }
    else{
        p->next = temp;
    }
}