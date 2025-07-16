#include "list.hpp"
#include <iostream>

// ---------------- NODE IMPLEMENTATION ----------------

Node::Node() : value(-1), next(nullptr) {}

Node::Node(int node_value) : value(node_value), next(nullptr) {}

int Node::get_value() {
    return this->value;
}

void Node::set_value(int node_value) {
    this->value = node_value;
}

Node* Node::get_next_node() {
    return this->next;
}

void Node::set_next_node(Node* next_node) {
    this->next = next_node;
}

// ---------------- LIST IMPLEMENTATION ----------------

List::List() {
    this->head = new Node();  
    this->last = this->head;
    this->size = 0;
}

List::~List() {
    Node* current = this->head;
    while (current != nullptr) {
        Node* to_delete = current;
        current = current->get_next_node();
        delete to_delete;
    }
    this->size = 0;
}

int List::get_size() {
    return this->size;
}

Node* List::get_head() {
    return this->head;
}

Node* List::poition(int pos, bool before) {
    if (pos > this->size || pos <= 0) {
        throw "Erro: posição inválida";
    }

    Node* current = this->head;
    for (int i = 0; i < pos - 1; i++) {
        current = current->get_next_node();
    }

    if (before) {
        return current;
    } else {
        return current->get_next_node();
    }
}

void List::insert_at_the_end(int new_value_node) {
    Node* new_node = new Node(new_value_node);
    this->last->set_next_node(new_node);
    this->last = new_node;
    this->size++;
}
