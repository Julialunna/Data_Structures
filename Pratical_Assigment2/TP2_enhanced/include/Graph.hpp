#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "List.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include <iostream>
#include <limits>

struct Edge {
    int dest;
    int peso;
};

template <typename T>
class Graph
{
public:
    Graph(int num_vertices);
    Graph();
    ~Graph();

    void InsertVertex();
    void InsertEdge(int v, int w, int peso);
    int VertexCount() const;
    int EdgeCount() const;
    void PrintNeighbors(int v) const;
    List<int>* FindNeighbors(int v) const;
    List<int> Dijkstra(int origem, int destino);
    List<Edge>* FindEdgeNeighbors(int v) const;
    List<int> BreadthFirstSearch(int vertex_origin, int vertex_destination);

private:
    List<Edge> **vertex;
    int num_vertex;
};

template <typename T>
Graph<T>::Graph(int num_vertices)
{
    this->num_vertex = num_vertices;
    this->vertex = new List<Edge> *[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        this->vertex[i] = new List<Edge>();
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
        delete this->vertex[i];
    delete[] this->vertex;
}

template <typename T>
void Graph<T>::InsertVertex()
{
    List<Edge> **novo_array = new List<Edge> *[this->num_vertex + 1];
    for (int i = 0; i < this->num_vertex; i++)
        novo_array[i] = this->vertex[i];
    novo_array[this->num_vertex] = new List<Edge>();
    delete[] this->vertex;
    this->vertex = novo_array;
    this->num_vertex++;
}

template <typename T>
void Graph<T>::InsertEdge(int v, int w, int peso)
{
    if (v < 0 || v >= num_vertex || w < 0 || w >= num_vertex)
        return;
    this->vertex[v]->insertEnd({w, peso});
    this->vertex[w]->insertEnd({v, peso});
}

template <typename T>
int Graph<T>::VertexCount() const
{
    return this->num_vertex;
}

template <typename T>
int Graph<T>::EdgeCount() const
{
    int total = 0;
    for (int i = 0; i < this->num_vertex; i++)
        total += this->vertex[i]->getSize();
    return total / 2;
}

template <typename T>
void Graph<T>::PrintNeighbors(int v) const
{
    if (v < 0 || v >= num_vertex)
        return;
    List<Edge>* neighbors = this->vertex[v];
    for (int i = 1; i <= neighbors->getSize(); i++) {
        Edge e = neighbors->getItem(i);
        std::cout << "(" << e.dest << ", peso " << e.peso << ") ";
    }
    std::cout << std::endl;
}

// Este método devolve uma lista com os índices dos vizinhos, compatível com List<int>
template <typename T>
List<int>* Graph<T>::FindNeighbors(int v) const
{
    if (v < 0 || v >= num_vertex)
        return nullptr;
    List<int>* neighbor_ids = new List<int>();
    List<Edge>* neighbors = this->vertex[v];
    for (int i = 1; i <= neighbors->getSize(); i++) {
        neighbor_ids->insertEnd(neighbors->getItem(i).dest);
    }
    return neighbor_ids;
}

template <typename T>
List<int> Graph<T>::Dijkstra(int origin, int destination)
{
    List<int> path;
    int* dist = new int[num_vertex];
    int* prev = new int[num_vertex];
    bool* visited = new bool[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        dist[i] = std::numeric_limits<int>::max();
        prev[i] = -1;
        visited[i] = false;
    }

    dist[origin] = 0;

    for (int i = 0; i < num_vertex; i++) {
        int u = -1;
        int minDist = std::numeric_limits<int>::max();
        for (int j = 0; j < num_vertex; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1)
            break;
        visited[u] = true;
        if (u == destination)
            break;
        List<Edge>* neighbors = vertex[u];
        for (int k = 1; k <= neighbors->getSize(); k++) {
            Edge e = neighbors->getItem(k);
            int v = e.dest;
            int peso = e.peso;
            if (!visited[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                prev[v] = u;
            }
        }
    }

    if (dist[destination] == std::numeric_limits<int>::max()) {
        delete[] dist;
        delete[] prev;
        delete[] visited;
        return path;
    }

    Stack<int> stack;
    for (int at = destination; at != -1; at = prev[at])
        stack.pile(at);

    while (!stack.empty())
        path.insertEnd(stack.unstack());

    delete[] dist;
    delete[] prev;
    delete[] visited;
    return path;
}
template <typename T>
List<Edge>* Graph<T>::FindEdgeNeighbors(int v) const
{
    if (v < 0 || v >= num_vertex)
        return nullptr;
    return this->vertex[v];
}

template <typename T>
List<int> Graph<T>::BreadthFirstSearch(int vertex_origin, int vertex_destination)
{
    List<int> path;
    if (vertex_origin < 0 || vertex_origin >= num_vertex || vertex_destination < 0 || vertex_destination >= num_vertex)
        return path;

    bool* visited = new bool[num_vertex];
    int* pred = new int[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        visited[i] = false;
        pred[i] = -1;
    }

    Queue<int> q;
    visited[vertex_origin] = true;
    q.queue(vertex_origin);

    while (q.getSize() != 0) {
        int u = q.dequeue();
        if (u == vertex_destination)
            break;

        List<Edge>* neighbors = vertex[u];
        for (int i = 1; i <= neighbors->getSize(); i++) {
            Edge e = neighbors->getItem(i);
            int v = e.dest;
            if (!visited[v]) {
                visited[v] = true;
                pred[v] = u;
                q.queue(v);
            }
        }
    }

    if (!visited[vertex_destination]) {
        delete[] visited;
        delete[] pred;
        return path;
    }

    Stack<int> stack;
    for (int v = vertex_destination; v != -1; v = pred[v]) {
        stack.pile(v);
    }
    while (!stack.empty()) {
        path.insertEnd(stack.unstack());
    }

    delete[] visited;
    delete[] pred;
    return path;
}

#endif
