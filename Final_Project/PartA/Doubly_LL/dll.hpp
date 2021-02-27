using namespace std;

struct Node{
    int key;
    Node * next;
    Node * prev;
};

class DoublyLinkedList{
    private:
        Node * head;
        Node * createNode(int key);
    public:
        DoublyLinkedList();
        Node * searchNodes(int key);
        void addNode(int key);
        void printNodes();
};