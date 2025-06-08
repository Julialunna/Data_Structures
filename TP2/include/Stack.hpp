#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>


template <typename T>
class Stack;

template <typename T>
class StackNode {
public:
    StackNode();
private:
    T item;
    StackNode<T>* next;
    friend class Stack<T>;
};

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();

    void pile(T item);

    T unstack();

    void clean();

    void print();

    T search(const T& key);

private:
    StackNode<T>* top;
    int size;
};

//O(1)
template <typename T>
StackNode<T>::StackNode() {
    this->next = nullptr;

}
//O(1)
template <typename T>
Stack<T>::Stack() {
    this->top = nullptr;
    this->size = 0;
}

//O(n), delete all nodes
template <typename T>
Stack<T>::~Stack() {
    this->clean();
}

//O(1), put item on top of pile 
template <typename T>
void Stack<T>::pile(T item) {
    StackNode<T>* new_node = new StackNode<T>();
    new_node->item = item;
    new_node->next = this->top;
    this->top = new_node;
    this->size++;
}
//O(1), gets node on top of pile and delete it 
template <typename T>
T Stack<T>::unstack() {
    if (this->size == 0) {
        throw "Error: stack is empty";
    }
    StackNode<T>* p = this->top;
    T aux = p->item;
    this->top = p->next;
    delete p;
    //reducing size 
    this->size--;
    return aux;
}
//O(n), deleting all nodes 
template <typename T>
void Stack<T>::clean() {
    while (this->size > 0) {
        this->unstack();
    }
}
//O(n)
template <typename T>
void Stack<T>::print() {
    StackNode<T>* p = this->top;
    //iterates over all stack and pritn items 
    while (p != nullptr) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;
}
//O(n)
template <typename T>
T Stack<T>::search(const T& key) {

    StackNode<T>* p = this->top;
    //iterating over pile looking for node with the key wanted
    while (p != nullptr) {
        if (p->item == key) {
            return p->item;
        }
        p = p->next;
    }
    return T();
}

#endif 