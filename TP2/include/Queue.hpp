#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>


template <typename T>
class Queue;

template <typename T>
class QueueNode {
public:
    QueueNode();
private:
    T item;
    QueueNode<T>* next;
    friend class Queue<T>;
};

template <typename T>
class Queue {
public:
    Queue();
    ~Queue();

    void queue(const T& item);

    T dequeue();

    void clean();

   
    void print();
    
    T search(const T& key);
    int getSize();

private:
    QueueNode<T>* front;  
    QueueNode<T>* back;   
    int size;
};

//O(1)
template <typename T>
QueueNode<T>::QueueNode() {
    this->next = nullptr;
    
}

//O(1)
//use of a sentinel, items start at this->front->next
template <typename T>
Queue<T>::Queue() {
   
    this->front = new QueueNode<T>();
    this->back  = this->front;
    this->size  = 0;
}

//O(n), deletes all nodes and front
template <typename T>
Queue<T>::~Queue() {
    this->clean();
    delete this->front;
}
//O(1), create node and insert it at the end
template <typename T>
void Queue<T>::queue(const T& item) {
    QueueNode<T>* new_node = new QueueNode<T>();
    new_node->item = item;
    this->back->next = new_node;
    this->back = new_node;
    this->size++;
}
//O(1)
template <typename T>
T Queue<T>::dequeue() {
    //if queue is empty throw error
    if (this->size == 0) {
        throw "Error: empty queue";
    }
    //makes second item be the firts at queue
    QueueNode<T>* p = this->front->next;  
    T aux = p->item;
    this->front->next = p->next;
    if (this->front->next == nullptr) {
    
        this->back = this->front;
    }
    //deletes node and reduce queue size
    delete p;
    this->size--;
    return aux;
}
//O(n)
template <typename T>
void Queue<T>::clean() {
    QueueNode<T>* p = this->front->next;
    //iterates over queue deleting nodes
    while (p != nullptr) {
        QueueNode<T>* temp = p;
        p = p->next;
        delete temp;
    }
    //makes back and front point to null
    this->front->next = nullptr;
    this->back = this->front;
    this->size = 0;
}
//O(n)
template <typename T>
void Queue<T>::print() {
    QueueNode<T>* p = this->front->next;
    //iterates over queue printing nodes
    while (p != nullptr) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;
}
//O(n)
template <typename T>
T Queue<T>::search(const T& key) {
    QueueNode<T>* p = this->front->next;
    //iterates over queue looking for node with the key wanted
    while (p != nullptr) {
        if (p->item == key) {
            return p->item;
        }
        p = p->next;
    }

    return T();
}

template <typename T>
int Queue<T>::getSize(){
    return this->size;
}


#endif 
