#include "graph.hpp"
#include "list.hpp"
#include <iostream>

Graph::Graph(int num_vertices)
{
    this->num_vertices = num_vertices;
    this->vertices = new List *[num_vertices];
    for (int i = 0; i < num_vertices; i++)
    {
        this->vertices[i] = new List();
    }
}

Graph::~Graph()
{
    for (int i = 0; i < num_vertices; i++)
    {
        delete this->vertices[i];
    }
    delete[] this->vertices;
}

void Graph::InsertEdge(int v, int w)
{
    this->vertices[v]->insert_at_the_end(w);
    this->vertices[w]->insert_at_the_end(v); 
}

int Graph::VertexCount() {
    return this->num_vertices;
}

int Graph::EdgeCount() {
    int total_edges = 0;
    for (int i = 0; i < num_vertices; i++) {
        total_edges += this->vertices[i]->get_size();
    }
    return total_edges / 2; // Each edge is counted twice
}
int Graph::MinimumDegree() {
    int min_degree = this->vertices[0]->get_size();
    for (int i = 1; i < num_vertices; i++) {
        int degree = this->vertices[i]->get_size();
        if (degree < min_degree) {
            min_degree = degree;
        }
    }
    return min_degree;
}
int Graph::MaximumDegree() {
    int max_degree = this->vertices[0]->get_size();
    for (int i = 1; i < num_vertices; i++) {
        int degree = this->vertices[i]->get_size();
        if (degree > max_degree) {
            max_degree = degree;
        }
    }
    return max_degree;
}
void Graph::PrintNeighbors(int v) {
    Node* current = this->vertices[v]->get_head()->get_next_node();
    while (current != nullptr) {
        std::cout << current->get_value();
        current = current->get_next_node();
        if (current != nullptr) {
            std::cout << " ";
        } else {
            std::cout << std::endl;
        }
    }
}