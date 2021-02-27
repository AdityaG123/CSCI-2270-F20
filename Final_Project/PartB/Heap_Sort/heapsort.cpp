#include "heapsort.hpp"
#include <iostream>

using namespace std;

//Constructor that initialize and create array
HeapSort::HeapSort(int bsize){
    tableval = new int[bsize];
    currval = 0;
    max = bsize;
}

void HeapSort::fixHeap(int n){                                                  //this is a min heap
    int root = n;                                                               //largest number
    int temp;
    int leftLeaf = (2 * n) + 1;                                                 //left child
    int rightLeaf = leftLeaf + 1;                                               //right child

    if(leftLeaf < currval && tableval[leftLeaf] > tableval[root]){
        root = leftLeaf;                                                        //check that the left child is not larger than parent, is it is, then set as root
    }

    if(rightLeaf < currval && tableval[rightLeaf] > tableval[root]){
        root = rightLeaf;                                                       //check that the right child is not larger than parent, is it is, then set as root
    }

    if(root != n){                                                              //if the parent gets replaced
        temp = tableval[n];
        tableval[n] = tableval[root];                                           //the value of the index moves to the new parent/root
        tableval[root] = temp;
        fixHeap(root);                                                          //recursivly call fixHeap with new root
    }
    
}

void HeapSort::insertHeap(int key){                                             
    tableval[currval] = key;                                                    //add a key to the array index
    currval = currval + 1;                                                      //increment the current index value
}

void HeapSort::sort(){                                                          
    int i;
    int j = (currval / 2) - 1;                                                  //anything between currval and (currval/2) - 1 will not have children
    for(i = j; i >= 0; i--){                                                    //if j is equal to the parent of the last value in the heap
        fixHeap(i);                                                             //recursivly call fixHeap with new root
    }
}

void HeapSort::printHeap(){
    for(int i = 0; i <= currval; i++){                                          //traverses the full array indicies
        cout << tableval[i] << "," ;                                            //print every index value in the table
    }
    cout << endl;
}

int HeapSort::empty(){                                                          //resets the current array index to be called in the driver
    currval = 0;    
    return currval;
}