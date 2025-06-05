#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

template <typename T>
class List;

template <typename T>
class ListNode {
public:
    ListNode();
private:
    T item;
    ListNode<T>* next;
    friend class List<T>;
};

template <typename T>
class List {
public:
    List();
    ~List();

    T getItem(int position);
    void setItem(T item, int position);

    void insertBeginning(T item);
    void insertEnd(T item);
    void insertAtPosition(T item, int position);

    T removeBeginning();
    T removeEnd();
    T removeAtPosition(int position);

    T search(const T& key);

    void print();
    void clean();

private:
    int size;
    ListNode<T>* first;
    ListNode<T>* last;

   
    ListNode<T>* position(int position);
};

//O(1)
template <typename T>
ListNode<T>::ListNode() {
    this->next = nullptr;
   
}

//O(1)
template <typename T>
List<T>::List() {
    // Criamos o sentinela em 'first'
    this->first = new ListNode<T>();
    this->last  = this->first;
    this->size  = 0;
}

//O(n)
template <typename T>
void List<T>::clean() {
    ListNode<T>* p = this->first->next;
    while (p != nullptr) {
        this->first->next = p->next;
        delete p;
        p = this->first->next;
    }
    this->last = this->first;
    this->size = 0;
}

//O(n)
template <typename T>
List<T>::~List() {
    this->clean();
    delete this->first;
}


// position one ListNode before the position. O(n) worst case
template <typename T>
ListNode<T>* List<T>::position(int position) {
    if (position > this->size || position <= 0) {
        throw "Error: invalid position";
    }
    ListNode<T>* p = this->first;
    // avançar exatamente (position - 1) passos a partir de 'first'
    for (int i = 1; i < position; i++) {
        p = p->next;
    }
    return p;
}


// position one ListNode before the position. O(n) worst case
template <typename T>
T List<T>::getItem(int position) {
    ListNode<T>* p = this->position(position);
    // p aponta para o nó ANTES de onde está o item
    return p->next->item;
}

//O(1)
template <typename T>
void List<T>::setItem(T item, int position) {
    ListNode<T>* p = this->position(position);
    p->next->item = item;
}
//O(1)
template <typename T>
void List<T>::insertBeginning(T item) {
    ListNode<T>* new_node = new ListNode<T>();
    new_node->item = item;
    new_node->next = this->first->next;
    this->first->next = new_node;
    this->size++;

    if (new_node->next == nullptr) {
        this->last = new_node;
    }
}

//O(1)
template <typename T>
void List<T>::insertEnd(T item) {
    ListNode<T>* new_node = new ListNode<T>();
    new_node->item = item;
    this->last->next = new_node;
    this->last = new_node;
    this->size++;
}

// worst case O(n)
template <typename T>
void List<T>::insertAtPosition(T item, int position) {
    ListNode<T>* p = this->position(position);
    ListNode<T>* new_node = new ListNode<T>();
    new_node->item = item;
    new_node->next = p->next;
    p->next = new_node;
    this->size++;

    if (new_node->next == nullptr) {
        this->last = new_node;
    }
}

//O(1)
template <typename T>
T List<T>::removeBeginning() {
    if (this->size == 0) {
        throw "Error: empty list";
    }
    ListNode<T>* p = this->first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == nullptr) {
        // Ficou vazia outra vez
        this->last = this->first;
    }
    T aux = p->item;
    delete p;
    return aux;
}

//O(1)
template <typename T>
T List<T>::removeEnd() {
    if (this->size == 0) {
        throw "Error: empty list";
    }
    // position(this->size) retorna o nó ANTES do último item
    ListNode<T>* p = this->position(this->size);
    p->next = nullptr;
    this->size--;
    T aux = this->last->item;
    delete this->last;
    this->last = p;
    return aux;
}

// worst case O(n)
template <typename T>
T List<T>::removeAtPosition(int position) {
    if (this->size == 0) {
        throw "Error: empty list";
    }
    ListNode<T>* p = this->position(position);
    ListNode<T>* q = p->next;
    p->next = q->next;
    this->size--;
    T aux = q->item;
    delete q;
    if (p->next == nullptr) {
        this->last = p;
    }
    return aux;
}
//worst case O(n)
template <typename T>
T List<T>::search(const T& key) {
    if (this->size == 0) {
        throw "Error: empty list";
    }
    ListNode<T>* p = this->first->next;
    while (p != nullptr) {
        if (p->item == key) {
            return p->item;
        }
        p = p->next;
    }
    
    return T();
}

//O(n)
template <typename T>
void List<T>::print() {
    ListNode<T>* p = this->first->next;
    while (p != nullptr) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

#endif
