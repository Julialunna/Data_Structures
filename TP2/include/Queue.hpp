#ifndef QUEUE_HPP
#define QUEUE_HPP
typedef int itemType;
typedef int keyType;
class Queue;

class QueueNode {
public:
    QueueNode();
private:
    itemType item; 
    QueueNode* next;
    friend class Queue;
};

class Queue{
    public: 
    Queue();
    ~Queue();
    void queue(itemType item);
    itemType dequeue();
    void clean();
    void print();
    itemType search(keyType key);
    private:
    QueueNode *front;
    QueueNode *back;
    int size;
};
#endif