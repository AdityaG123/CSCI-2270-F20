#include "bubblesort.hpp"
#include <iostream>

using namespace std;

//Constructor that initializes and create array
BubbleSort::BubbleSort(int bsize){
    tableval = new int[bsize];
    size = bsize;
    currval = 0;
}

bool BubbleSort::insertArray(int key){
    if(currval == size){                                    //if the current index is at the size of the array then dont add more values
        return false;
    }
    tableval[currval] = key;                                //if not, then add a key to the array index
    currval = currval + 1;                                  //increment the current index value
    return true;
}

int BubbleSort::searchArray(int key){
    for(int i = 0; i < size; i++){                          //from 0 to the size of the array
        if(tableval[i] == key){                             //traverse array to find the element
            return i;                                       //return the element if found
        }
    }
    return -1;
}

void BubbleSort::printArray(){
    for(int i = 0; i <= currval; i++){                      //traverses the full array indicies
        cout << tableval[i] << ",";                         //print every index value in the table
    }
    cout << endl;
}

bool BubbleSort::sort(){                                   
    int i = 0;
    int j = 0;
    while (i < currval){                                    //while the the first value is less than the array index
        while(j < currval - i){                             //while the the second value is less than the array index - the first value
            if (tableval[j] > tableval[j + 1]){             //if the element at j + 1 is larger than j, then swap elements
                int temp = tableval[j];
                tableval[j] = tableval[j + 1];
                tableval[j + 1] = temp;
            }
            j++;                                            //increment the second value
        }
        i++;                                                //increment the first value
        j = 0;                                              //resets the value of j
    }
    return true;
}

int BubbleSort::empty(){                                    //resets the current array index to be called in the driver
    currval = 0;
    return currval;
}