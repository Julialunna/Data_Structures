#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T>
class List;

template <typename T>
class ListNode
{
public:
    ListNode();

private:
    T item;
    ListNode<T> *next;
    friend class List<T>;
};

template <typename T>
class List
{
public:
    List();
    ~List();
    List(const List<T> &other)
        : first(new ListNode<T>()),
          last(first),
          size(0)
    {
        for (ListNode<T> *p = other.first->next; p; p = p->next)
            insertEnd(p->item);
    }
    List<T> &operator=(const List<T> &other)
    {
        if (this != &other) {
            clean();
            for (ListNode<T> *p = other.first->next; p; p = p->next)
                insertEnd(p->item);
        }
        return *this;
    }

    T& getItem(int position);
    void setItem(T item, int position);

    void insertBeginning(T item);
    void insertEnd(T item);
    void insertAtPosition(T item, int position);

    T removeBeginning();
    T removeEnd();
    T removeAtPosition(int position);

    T& search(const int key);
    int getSize() const;

    void print();
    void clean();

private:
    ListNode<T> *first;
    ListNode<T> *last;
    int size;
    ListNode<T> *position(int position);
};

template <typename T>
ListNode<T>::ListNode()
{
    this->next = nullptr;
}

template <typename T>
List<T>::List()
{
    this->first = new ListNode<T>();
    this->last = this->first;
    this->size = 0;
}

template <typename T>
void List<T>::clean()
{
    if (this->first == nullptr) {
        std::cerr << " ERRO: this->first é nullptr no clean()\n";
        return;
    }
    ListNode<T> *p = this->first->next;
    while (p != nullptr) {
        this->first->next = p->next;
        delete p;
        p = this->first->next;
    }
    this->last = this->first;
    this->size = 0;
}

template <typename T>
List<T>::~List()
{
    this->clean();
    delete this->first;
}

template <typename T>
int List<T>::getSize() const
{
    return this->size;
}

template <typename T>
ListNode<T> *List<T>::position(int position)
{
    if (position > this->size || position <= 0)
        std::cerr << "Error: invalid position\n";
    ListNode<T> *p = this->first;
    for (int i = 1; i < position; i++)
        p = p->next;
    return p;
}

template <typename T>
T& List<T>::getItem(int position)
{
    ListNode<T> *p = this->position(position);
    return p->next->item;
}

template <typename T>
void List<T>::setItem(T item, int position)
{
    ListNode<T> *p = this->position(position);
    p->next->item = item;
}

template <typename T>
void List<T>::insertBeginning(T item)
{
    ListNode<T> *new_node = new ListNode<T>();
    new_node->item = item;
    new_node->next = this->first->next;
    this->first->next = new_node;
    this->size++;
    if (new_node->next == nullptr)
        this->last = new_node;
}

template <typename T>
void List<T>::insertEnd(T item)
{
    ListNode<T> *new_node = new ListNode<T>();
    new_node->item = item;
    this->last->next = new_node;
    this->last = new_node;
    this->size++;
}

template <typename T>
void List<T>::insertAtPosition(T item, int position)
{
    ListNode<T> *p = this->position(position);
    ListNode<T> *new_node = new ListNode<T>();
    new_node->item = item;
    new_node->next = p->next;
    p->next = new_node;
    this->size++;
    if (new_node->next == nullptr)
        this->last = new_node;
}

template <typename T>
T List<T>::removeBeginning()
{
    if (this->size == 0)
        std::cerr << "Error: empty list\n";
    ListNode<T> *p = this->first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == nullptr)
        this->last = this->first;
    T aux = p->item;
    delete p;
    return aux;
}

template <typename T>
T List<T>::removeEnd()
{
    if (this->size == 0)
        std::cerr << "Error: empty list\n";
    ListNode<T> *p = this->position(this->size);
    p->next = nullptr;
    this->size--;
    T aux = this->last->item;
    delete this->last;
    this->last = p;
    return aux;
}

template <typename T>
T List<T>::removeAtPosition(int position)
{
    if (this->size == 0)
        std::cerr << "Error: empty list\n";
    ListNode<T> *p = this->position(position);
    ListNode<T> *q = p->next;
    p->next = q->next;
    this->size--;
    T aux = q->item;
    delete q;
    if (p->next == nullptr)
        this->last = p;
    return aux;
}

template <typename T>
T& List<T>::search(const int key)
{
    if (this->size == 0)
        std::cerr << "Error: empty list\n";
    ListNode<T> *p = this->first->next;
    while (p != nullptr) {
        if (p->item == key)
            return &p->item;
        p = p->next;
    }
    return nullptr;
}

template <typename T>
void List<T>::print()
{
    ListNode<T> *p = this->first->next;
    while (p != nullptr) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

#endif
