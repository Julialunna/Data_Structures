#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "List.hpp"
#include <iostream>

template <typename T>
class Graph {
public:
  
    Graph(int num_vertices);

   
    ~Graph();

    
    void InsertVertex();

    // Aqui, 'data_for_w' deve ser algo que represente a conexão de v→w (por exemplo, o índice w
    // ou uma struct que contenha w mais algum payload). 
    // Similarmente, 'data_for_v' é o dado que vamos inserir em w para indicar a aresta w→v.
    void InsertEdge(int v, const T& data_for_w, int w, const T& data_for_v);

    int VertexCount() const;

    int EdgeCount() const;

    void PrintNeighbors(int v) const;

    List<T>* FindNeighbors(int v) const;

private:
    List<T>** vertices; 
    int num_vertices;
};

template <typename T>
Graph<T>::Graph(int num_vertices) {
    this->num_vertices = num_vertices;
    this->vertices = new List<T>*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        this->vertices[i] = new List<T>(); // cada vértice começa com lista vazia
    }
}

template <typename T>
Graph<T>::~Graph() {
    for (int i = 0; i < this->num_vertices; i++) {
        delete this->vertices[i];
    }
    delete[] this->vertices;
}

template <typename T>
void Graph<T>::InsertVertex() {
    List<T>** novo_array = new List<T>*[this->num_vertices + 1];
    for (int i = 0; i < this->num_vertices; i++) {
        novo_array[i] = this->vertices[i];
    }
    novo_array[this->num_vertices] = new List<T>();
    delete[] this->vertices;
    this->vertices = novo_array;
    this->num_vertices++;
}

template <typename T>
void Graph<T>::InsertEdge(int v, const T& data_for_w, int w, const T& data_for_v) {
    if (v < 0 || v >= num_vertices || w < 0 || w >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    this->vertices[v]->insertEnd(data_for_w);

    this->vertices[w]->insertEnd(data_for_v);
}

template <typename T>
int Graph<T>::VertexCount() const {
    return this->num_vertices;
}

template <typename T>
int Graph<T>::EdgeCount() const {
    int total = 0;
    for (int i = 0; i < this->num_vertices; i++) {
        total += this->vertices[i]->getSize();
    }

    return total / 2;
}

template <typename T>
void Graph<T>::PrintNeighbors(int v) const {
    if (v < 0 || v >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    this->vertices[v]->print();
}

template <typename T>
List<T>* Graph<T>::FindNeighbors(int v) const {
    if (v < 0 || v >= num_vertices) {
        throw "Error: invalid vertex index";
    }
    return this->vertices[v];
}

#endif
