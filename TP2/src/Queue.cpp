#include "Queue.hpp"
#include <iostream>

// O(1)
QueueNode::QueueNode()
{
    this->item = -1;
    this->next = nullptr;
}
//O(1)
//use of a sentinel
Queue::Queue(){
    this->front = new QueueNode();
    this->back = this->front;
    this->size = 0;
}
//O(n)
Queue::~Queue(){
    this->clean();
    delete this->front;
}
//O(13)
void Queue::queue(itemType item){
    QueueNode *new_node = new QueueNode();
    new_node->item = item;
    this->back->next = new_node;
    this->back = new_node;
    this->size++;
}
//O(1)
itemType Queue::dequeue(){
    QueueNode *p;
    itemType aux;

    if(this->size == 0){
        throw "Error: empty list";
    }

    aux = this->front->next->item;
    p = this->front->next;
    this->front->next = p->next;

    if (this->front->next == nullptr) {
        this->back = this->front;
    }

    delete p;
    this->size--;
    return aux;
}
//O(n)
void Queue::clean(){
    QueueNode  *p;
    p = this->front->next;
    while(p!=nullptr){
        QueueNode *temp = p;
        p = p->next;
        delete temp;
    }
    this->front->next = nullptr;
    this->size = 0;
    this->back = this->front;
}
//O(n)
void Queue::print(){
    QueueNode  *p;
    p = this->front->next;
    while(p!=nullptr){
        std::cout<<p->item<<" ";
        p = p->next;
    }
    std::cout<<std::endl;
}
//O(n)
itemType Queue::search(keyType key){
    QueueNode  *p;
    p = this->front->next;
    while(p!=nullptr){
        if(p->item == key){
            return p->item;
        }
        p = p->next;
    }

    return -1;
}