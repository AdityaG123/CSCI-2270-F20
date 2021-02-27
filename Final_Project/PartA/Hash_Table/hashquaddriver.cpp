#include "hashquad.hpp"
#include <chrono>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace std::chrono;


void randval(int * arr, int val){                                           //randomly generates 100 values to be called by driver main 
    for(int i = 0; i < 100; i++){   
        arr[i] = rand() % val;
    }
}

int main(int argc, char** argv) {

    int array[10000];
    int timeInterval = 100;
    float insertInHash[100];                                                //creates a time array to insert into hash table
    float searchFromHash[100];                                              //creates a time array to search from hash table
    int insertCollision[100];                                               //creates a time array to count the number of collisions while inserting to hash table
    int searchCollision[100];                                               //creates a time array to count the number of collisions while searching from hash table

    HashTable* HASH = new HashTable(40009);                                 //constructs new hash table of size 40009

    ifstream iFile;                                                         //opens a new input data file
    string temp, list;

    int a = 0;

    iFile.open("dataSetA.csv");
    while(getline(iFile, temp, ',')) {                                      //takes all values from the input csv file and adds them to an array
        array[a] = stoi(temp);;
        a++;
    } 
    iFile.close();                                                          //closes the input data file

    
    high_resolution_clock::time_point start;                                // starts the timing clock 
    high_resolution_clock::time_point end;                                  //ends the timing clock
    duration<float> exectime;


    for(int j = 0; j < timeInterval; j++){                                  //sets the amount of iterations for the timing
        
        start = high_resolution_clock::now();                               //starts the clock
        for(int i = 0; i < 100; i++){
            HASH->insert(array[i+j*100]);                                   //inserts the data into a test array and adds 100 data points in array for each iteration
        }
        end = high_resolution_clock::now();                                 //ends timing clock
        exectime = duration_cast<nanoseconds>(end - start);
        insertInHash[j] = (exectime.count()/100);                           //find average time to insert into array from hash table

        insertCollision[j] = HASH->getNumOfCollision();                     //retrieves the number of collisions that has occurred while inserting into hash


        int rand[100];                                                      //creates an array of 100 pseudo-randomly generated numbers that adds by 100 for every iteration up to 10,000
        randval(rand, 100*(j + 1));


        start = high_resolution_clock::now();                               //starts the clock
        for(int i = 0; i< 100;i++){
            HASH->search(array[rand[i]]);                                   //searches from the hash table and puts into a test array and uses 100 pseudo randomly generated numbers for each iteration
        }
        end = high_resolution_clock::now();                                 //ends timing clock
        exectime = duration_cast<nanoseconds>(end - start);
        searchFromHash[j] = (exectime.count()/(100));                       //find average time to search from array from hash table

        searchCollision[j] = HASH->getNumOfCollision();                     //retrieves the number of collisions that has occurred while searching from hash
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


    ofstream insertFile ("insert_search_performance_hash_dataSetA.csv");                //creates a output .csv file
    if(insertFile.is_open()){                                                           //checks to see if the file has been opened
        for(int i = 0; i < 99; i++){                                                    //adds all insert timing into hash
            insertFile << insertInHash[i] << ",";
        }
        insertFile << insertInHash[99];                                                 //adds final insert timing

        insertFile << "\n";

        for(int k = 0; k < 99; k++){                                                    //adds all hash collisions when inserting into hash
            insertFile << insertCollision[k] << ",";
        }
        insertFile << insertCollision[99] ;                                             //adds final insert collision

        insertFile << "\n";

        for(int j = 0; j < 99; j++){                                                    //adds all search timing from hash
            insertFile << searchFromHash[j] << ",";
        }
        insertFile << searchFromHash[99];                                               //adds final search collision

        insertFile << "\n";

        for(int l = 0; l < 99; l++){                                                    //adds all hash collisions when searching from hash
            insertFile << searchCollision[l] << ",";
        }
        insertFile << searchCollision[99];                                              //adds final search collision

        insertFile.close();                                                             //closes output file
    }
}
