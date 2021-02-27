#include "dll.hpp"
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;


void randval(int * arr, int val){                               //randomly generates 100 values to be called by driver main 
    for(int i = 0; i < 100; i++){
        arr[i] = rand() % val;
    }
}

int main(int argc, char** argv) {

    int array[10000];
    int timeInterval = 100;
    float insertInDll[100];                                     //creates a time array to insert into DLL
    float searchFromDll[100];                                   //creates a time array to search from DLL

    DoublyLinkedList* DLL = new DoublyLinkedList();             //constructs new Doubly Linked list

    ifstream iFile;                                             //opens a new input data file
    string temp;

    int a = 0;
    iFile.open("dataSetA.csv");
    while(getline(iFile, temp, ',')) {                          //takes all values from the input csv file and adds them to an array
        array[a] = stoi(temp);;
        a++;
    } 
    iFile.close();                                              //closes the input data file
    
    high_resolution_clock::time_point start;                    // starts the timing clock 
    high_resolution_clock::time_point end;                      //ends the timing clock
    duration<float> exectime;


    for(int j = 0; j < timeInterval; j++){                      //sets the amount of iterations for the timing
        
        start = high_resolution_clock::now();                   //starts the clock
        for(int i = 0; i < 100; i++){                           //inserts the data into a test array and adds nodes for each
            DLL->addNode(array[i]);
        }
        end = high_resolution_clock::now();                     //ends timing clock
        exectime = duration_cast<nanoseconds>(end - start);     
        insertInDll[j] = (exectime.count()/100);                //check and calculates the average insert time into the DLL


        int rand[100];                                          //creates an array of 100 pseudo-randomly generated numbers that adds by 100 for every iteration up to 10,000
        randval(rand, 100*(j + 1));


        start = high_resolution_clock::now();                   //starts the clock
        for(int i = 0; i< 100;i++){                             //searches for the data from the test array by using a random value that has been generated.
            DLL->searchNodes(array[rand[i]]);
        }
        end = high_resolution_clock::now();                     //ends the clock
        exectime = duration_cast<nanoseconds>(end - start);
        searchFromDll[j] = (exectime.count()/(100));            //checks and calculates the average serach time from the DLL
    }


    // for(int i = 0; i < 100; i++){
    //     cout << insertInDll[i] << "    ";
    //     cout << searchFromDll[i] << endl;
    // }

    // ofstream insertFile ("insert_performance_doubly_ll_dataSetA.csv");
    // if(insertFile.is_open()){
    //     for(int i = 0; i < 99; i++){
    //     insertFile << insertInDll[i] << ",";
    //     }
    //     insertFile << insertInDll[100];
    //     insertFile.close();
    // }

    // ofstream searchFile ("search_performance_doubly_ll_dataSetA.csv");
    // if(searchFile.is_open()){
    //     for(int i = 0; i < 99; i++){
    //         searchFile << searchFromDll[i] << ",";
    //     }
    //     searchFile << searchFromDll[100];
    //     searchFile.close();
    // }


    ofstream insertFile ("insert_search_performance_doubly_ll_dataSetA.csv");       //creates a output .csv file 
    if(insertFile.is_open()){                                                       //checks to see if the file has been opened
        for(int i = 0; i < 99; i++){                                                //goes through all 100 outputted data points and sets them into cvs
            insertFile << insertInDll[i] << ",";                                    //adds all insert timing from DLL
        }
        insertFile << insertInDll[99];                                              //adds final insert timing

        insertFile << "\n";

        for(int j = 0; j < 99; j++){
            insertFile << searchFromDll[j] << ",";                                  //adds all search timing from DLL
        }
        insertFile << searchFromDll[99];                                            //adds final search timing
        
        insertFile.close();                                                         //closes output file
    }
}
