#include "Stack.hpp"
#include <iostream>

// O(1)
StackNode::StackNode()
{
    this->item = -1;
    this->next = nullptr;
}
// O(n)
Stack::Stack()
{
    this->top = nullptr;
    this->size = 0;
}
// O(n)
Stack::~Stack()
{
    this->clean();
}

// O(1)
void Stack::pile(itemType item)
{
    StackNode *new_node = new StackNode();
    new_node->item = item;
    new_node->next = this->top;
    this->top = new_node;
    this->size++;
}
// O(1)
itemType Stack::unstack()
{
    itemType aux;
    StackNode *p;
    if (this->size == 0)
    {
        throw "Error: stack is empty";
    }

    aux = this->top->item;
    p = this->top;
    this->top = this->top->next;
    delete p;
    this->size--;
    return aux;
}

//O(n)
void Stack::clean()
{
    while (this->size > 0)
    {
        this->unstack();
    }
}

void Stack::print(){
    StackNode *p = this->top;
    while (p != nullptr) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;
    
}