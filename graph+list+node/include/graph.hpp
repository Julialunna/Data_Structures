#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "list.hpp"

/* You may include any necessary headers for your class to function.
 * No other changes to this file are allowed.
 */

class Graph {
public:
    Graph(int num_vertices);
    ~Graph();

    void InsertVertex();
    void InsertEdge(int v, int w);

    int VertexCount();
    int EdgeCount();

    int MinimumDegree();
    int MaximumDegree();

    void PrintNeighbors(int v);


private:

    /* You must implement AdjacencyList as an ADT that will store
     * the graph's data. Remember that this ADT must be a linked list.
     */
    List** vertices;
    int num_vertices;
};

#endif
