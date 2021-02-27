#include "hashquad.hpp"
#include <iostream>

using namespace std;

//Constructor that sets all the elements in the hash table to -1
HashTable::HashTable(int bsize){
    tableSize = bsize;
    table = new int[bsize];
    for(int i = 0; i < bsize; i++){
        table[i] = -1;
    }
}

bool HashTable::insert(int key){
    int index = hashFunction(key);                          //find the first index of the hash table
    int i;
    int check;
    for(i = 0; i < tableSize; i++){                         //for every value incremented through the tableSize
        check = (index + (i*i)) % tableSize;                //quadratic probing
        if(table[check] == -1 ){                            //if the value in the table is -1, then insert the key into that index
            table[check] = key;
            return true;
        }
        numOfcolision++;                                    //if it is not -1, then increment the number of collisions and do quadratic probing again
    }
    return false;
}

unsigned int HashTable::hashFunction(int key){
    return (key % tableSize);                               //craetes a hash function used to find the available indicies
}

void HashTable::printTable(){
    for(int i = 0; i < tableSize; i++){                     //traverse the table and output the data in the table
        cout << table[i] << " ";
    }
    cout << endl;
}

int HashTable::getNumOfCollision(){                         //resets the number of collisions to 0 after every iteration when 100 is added to the tableSize used in driver
    int collision = numOfcolision;
    numOfcolision = 0;
    return collision;                                       //returns the collisions  
}

int HashTable::search(int key){                             //similar to insert function
    int index = hashFunction(key);                          //find the first index of the hash table
    int i = 0;
    int check = (index + i*i) % tableSize;                  //quadratic probing
    for(int i = 1; i < tableSize; i++){
        if(table[check] == key ){                           //if the index is there then return the index
            return check;
        }
        else{
            check = hashFunction((index + (i*i)) % tableSize);       //search till you find the key in an index
            numOfcolision++;                                         //if the index is filled, then increment the number of collisions
        }
    }
    return -1;
}