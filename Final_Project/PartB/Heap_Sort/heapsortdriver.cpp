#include "heapsort.hpp"
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;


int main(int argc, char** argv){

    int testData[10000];
    float sort[100];
  
    ifstream ifile;                                                 //opens a new input data file
    string temp;

    int a = 0; 

    ifile.open("dataSetA.csv");
    while(getline(ifile, temp, ',')) {                              //takes all values from the input csv file and adds them to an array
        testData[a] = stoi(temp);;
        a++;
    }  
    ifile.close();                                                  //closes the input data file

    HeapSort* HS = new HeapSort(10000);                             //constructs new Heap Sort data struct

 
    high_resolution_clock::time_point start;                        // starts the timing clock
    high_resolution_clock::time_point end;                          //ends the timing clock
    duration<float> exectime;

    for(int i = 0; i < 100; i++){                                   //sets the amount of iterations for the timing
        int j, k;
        j = (i + 1) * 100;                                          //adds a new array with 100 more values than previous and then increments for every increment of i

        HS->empty();                                                //resets the indicies value for the heap sort, starts over
           

        for(k = 0; k < j; k++){
            HS->insertHeap(testData[k]);                            //inserts based on for loop 100 times into heap 
        }


        start = high_resolution_clock::now();                       //starts the clock
        HS->sort();                                                 //heap sort through the array
        end = high_resolution_clock::now();                         //ends the clock
    
        exectime = duration_cast<nanoseconds>(end - start);
        sort[i] = exectime.count();                                 //check the sort time of the full heap sort per iteration
    }

    //HS->printHeap();


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

    ofstream outputFile ("insert_sort_performance_heapsort_dataSetA.csv");              //creates a output .csv file
    if (outputFile.is_open()){                                                          //checks to see if the file has been opened
        for(int i = 1; i < 100; i++){                                                   //goes through all 100 outputted data points and sets them into cvs
            outputFile << sort[i] << "\n";                                              //outputs the timing of the heap sort per iteration from the array to the csv file
        }
        outputFile << sort[99];                                                         //adds final heap sort iteration timing
        outputFile.close();                                                             //closes output file
    }
    return 0;
}