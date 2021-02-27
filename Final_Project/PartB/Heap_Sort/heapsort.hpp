#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

using namespace std;

class HeapSort{
    private:
        int currval;
        int *tableval;
        int max;
        void fixHeap(int n);

    public:
        HeapSort(int bsize);
        void insertHeap(int key);
        void sort();
        void printHeap();
        int searchHeap(int key);
        int empty();
};

#endif