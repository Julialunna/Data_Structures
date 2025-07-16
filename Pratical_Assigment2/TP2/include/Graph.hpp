#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "List.hpp"
#include "Queue.hpp"
#include <iostream>
#include <stdexcept>

template <typename T>
class Graph
{
public:
    Graph(int num_vertices);
    Graph();
    ~Graph();

    void InsertVertex();

    void InsertEdge(int v, int w);

    int VertexCount() const;

    int EdgeCount() const;

    void PrintNeighbors(int v) const;

    List<T> *FindNeighbors(int v) const;

    List<int> BreadthFirstSearch(int vertex_origin, int vertex_destination);

private:
    List<T> **vertex;
    int num_vertex;
};

template <typename T>
Graph<T>::Graph(int num_vertices)
{
    this->num_vertex = num_vertices;
    this->vertex = new List<T> *[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        this->vertex[i] = new List<T>(); // each vertex starts with an empty list
    }
}

template <typename T>
Graph<T>::Graph()
{
    this->num_vertex = 0;
}

template <typename T>
Graph<T>::~Graph()
{
    for (int i = 0; i < this->num_vertex; i++)
    {
        delete this->vertex[i];
    }
    delete[] this->vertex;
}

template <typename T>
void Graph<T>::InsertVertex()
{
    // create a new list with one more item
    List<T> **novo_array = new List<T> *[this->num_vertex + 1];
    for (int i = 0; i < this->num_vertex; i++)
    {
        novo_array[i] = this->vertex[i];
    }
    novo_array[this->num_vertex] = new List<T>();
    delete[] this->vertex;
    this->vertex = novo_array;
    this->num_vertex++;
}

template <typename T>
void Graph<T>::InsertEdge(int v, int w)
{
    // check if index are valid
    if (v < 0 || v >= num_vertex || w < 0 || w >= num_vertex)
    {
        std::cerr<<"Error: invalid vertex index"<<std::endl;
    }
    this->vertex[v]->insertEnd(w);

}

// return number of vertex
template <typename T>
int Graph<T>::VertexCount() const
{
    return this->num_vertex;
}

// return graph number of edges
template <typename T>
int Graph<T>::EdgeCount() const
{
    int total = 0;
    for (int i = 0; i < this->num_vertex; i++)
    {
        total += this->vertex[i]->getSize();
    }

    return total / 2;
}

// print neighbors
template <typename T>
void Graph<T>::PrintNeighbors(int v) const
{
    if (v < 0 || v >= num_vertex)
    {
        std::cerr<< "Error: invalid vertex index"<<std::endl;
    }
    this->vertex[v]->print();
}

// returns all vertex neighbors
template <typename T>
List<T> *Graph<T>::FindNeighbors(int v) const
{
    if (v < 0 || v >= num_vertex)
    {
        std::cerr<< "Error: invalid vertex index"<<std::endl;
    }
    return this->vertex[v];
}

// find minimum path between two vertex
// time complexity O(v+e) memory complexity O(v)
template <typename T>
List<int> Graph<T>::BreadthFirstSearch(int vertex_origin, int vertex_destination)
{
    List<int> path;

    // creating and initializing predecessors and visited vertex arrays
    bool* visited_vertex = new bool[this->num_vertex];
    int*  pred           = new int[this->num_vertex];
    for (int i = 0; i < this->num_vertex; i++) {
        visited_vertex[i] = false;
        pred[i]           = -1;
    }

    // visiting origin vertex
    Queue<int> q;
    visited_vertex[vertex_origin] = true;
    q.queue(vertex_origin);

    // executing Breadth First Search
    while (q.getSize()!=0) {
        int u = q.dequeue();
        if (u == vertex_destination) {
            break;
        }

        List<T>* neighbors = this->vertex[u];
        for (int i = 1; i <= neighbors->getSize(); i++) {
            int v = static_cast<int>(neighbors->getItem(i));
            if (!visited_vertex[v]) {
                visited_vertex[v] = true;
                pred[v]           = u;
                q.queue(v);
            }
        }
    }

    // if destination vertex wasn't reached returns empty list
    if (!visited_vertex[vertex_destination]) {
        delete[] visited_vertex;
        delete[] pred;
        return path;
    }

    // stack in the list in the right order 
    int* stack = new int[this->num_vertex];
    int  count = 0;
    for (int current = vertex_destination; current != -1; current = pred[current]) {
        stack[count++] = current;
    }
    for (int i = count - 1; i >= 0; i--) {
        path.insertEnd(stack[i]);
    }

    delete[] visited_vertex;
    delete[] pred;
    delete[] stack;
    return path;
}


#endif
