#include "Graph.hpp"
#include <iostream>

Graph::Graph(int num_vertices) {
    this->num_vertices = num_vertices;
    this->vertices = new List<int>*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        this->vertices[i] = new List<int>(); 
    }
}

Graph::~Graph() {
    for (int i = 0; i < this->num_vertices; i++) {
        delete this->vertices[i];
    }
    delete[] this->vertices;
}

void Graph::InsertVertex() {
    List<int>** novo_array = new List<int>*[this->num_vertices + 1];

    for (int i = 0; i < this->num_vertices; i++) {
        novo_array[i] = this->vertices[i];
    }

    novo_array[this->num_vertices] = new List<int>();

    delete[] this->vertices;
    this->vertices = novo_array;
    this->num_vertices++;
}

void Graph::InsertEdge(int v, int w) {
    if (v < 0 || v >= num_vertices || w < 0 || w >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    this->vertices[v]->insertEnd(w);
    
    this->vertices[w]->insertEnd(v);
}

int Graph::VertexCount() const {
    return this->num_vertices;
}

int Graph::EdgeCount() const {
    int total = 0;
    for (int i = 0; i < this->num_vertices; i++) {
        total += this->vertices[i]->getSize();
    }
    return total / 2;
}

void Graph::PrintNeighbors(int v) const {
    if (v < 0 || v >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    this->vertices[v]->print();
}

//O(1)
List<int>* Graph::FindNeighbors(int v) const {
    if (v < 0 || v >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    return this->vertices[v];
}