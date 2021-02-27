#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

using namespace std;

class BubbleSort{
    private:
    int currval;
    int *tableval;
    int size;
    int key;

    public:
        BubbleSort(int bsize);
        bool insertArray(int key);
        int searchArray(int key);
        void printArray();
        bool sort();
        int empty();
    
};

#endif