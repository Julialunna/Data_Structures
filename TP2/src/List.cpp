#include "List.hpp"
#include <iostream>
//O(1)
ListNode::ListNode(){
    this->item = -1;
    this->next = nullptr;
}

// O(1)
//usage of sentinel
List::List()
{
    this->first = new ListNode();
    this->first->item = -1;
    this->last = first;
}

//O(n)
void List::clean(){
    ListNode *p;
    p=this->first->next;
    while(p!=nullptr){
        this->first->next = p->next;
        delete p;
        p = this->first->next;
    }
    this->last = this->first;
    this->size = 0;
}

// O(n)
List::~List()
{
    this->clean();
    delete this->first;
}

// position one ListNode before the position. O(n) worst case
ListNode *List::position(int position)
{
    ListNode *p;
    int i = 0;
    if (position > this->size || position <= 0)
    {
        throw "Error: invalid position";
    }
    p = this->first;
    for (i = 1; i < position; i++)
    {
        p = p->next;
    }
    return p;
}
// O(n) worst case
itemType List::getItem(int position)
{
    ListNode *p;
    p = this->position(position);
    return p->next->item;
}
// O(n) worst case
void List::setItem(itemType item, int position)
{
    ListNode *p;
    p = this->position(position);
    p->next->item = item;
}
// O(1)
void List::insertBeginning(itemType item)
{
    ListNode *new_node = new ListNode();
    new_node->item = item;
    new_node->next = this->first->next;
    this->first->next = new_node;
    this->size++;
    if (new_node->next == nullptr)
    {
        this->last = new_node;
    }
}

// O(1)
void List::insertEnd(itemType item)
{
    ListNode *new_node = new ListNode();
    new_node->item = item;
    this->last->next = new_node;
    this->last = new_node;
    this->size++;
}

// worst case O(n)
void List::insertAtPosition(itemType item, int position)
{
    ListNode *p =  nullptr, *new_node = nullptr;
    p = this->position(position);
    new_node = new ListNode();
    new_node->item = item;
    new_node->next = p->next;
    p->next = new_node;
    this->size++;
    if (new_node->next == nullptr)
    {
        this->last = new_node;
    }
}
// O(1)
itemType List::removeBeginning()
{
    itemType aux;
    ListNode *p = nullptr;

    if (this->size == 0)
    {
        throw "Error: empty list";
    }
    p = this->first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == nullptr)
    {
        this->last = first;
    }

    aux = p->item;
    delete p;

    return aux;
}
// O(n)
itemType List::removeEnd()
{
    itemType aux;
    ListNode *p = nullptr;

    if (this->size == 0)
    {
        throw "Error: empty list";
    }
    p = this->position(this->size);

    p->next = nullptr;
    this->size--;
    aux = this->last->item;
    delete this->last;
    this->last = p;

    return aux;
}
// worst case O(n)
itemType List::removeAtPosition(int position)
{
    itemType aux;
    ListNode *p= nullptr, *q = nullptr;

    if (this->size == 0)
    {
        throw "Error: empty list";
    }
    p = this->position(position);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->item;
    delete q;
    if (p->next == nullptr)
    {
        this->last = p;
    }
    return aux;
}
//worst case O(n)
itemType List::search(keyType key)
{
    itemType aux;
    ListNode *p;
    if (this->size == 0)
    {
        throw "Error empty list";
    }
    p = this->first->next;
    aux = -1;
    while (p != nullptr)
    {
        if (p->item == key)
        {
            aux = p->item;
            break;
        }
        p = p->next;
    }
    return aux;
}
//O(n)
void List::print(){
    ListNode *p;
    p=this->first->next;
    while(p!=nullptr){
        std::cout<<p->item<<" "<<std::ends;
        p=p->next;
    }
    std::cout<<std::endl;

}