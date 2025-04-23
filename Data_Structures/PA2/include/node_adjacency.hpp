#ifndef NODE_ADJACENCY_HPP
#define NODE_ADJACENCY_HPP
#include <iostream>
#include "list.hpp"
#include "node.hpp"
class No_adjacencia{
    private:    
        int num_vertice;
        Lista* lista_adjacencia;
        No_adjacencia* proximo_no;
    public:
        No_adjacencia();
        No_adjacencia(int num_vertice);
        Lista* get_lista();
        void set_lista(Lista* lista_adjacencia_no);
        int get_num_vertice();
        void set_num_vertice(int num_vertice_no);
        No_adjacencia* get_proximo_no_adjacencia();
        void set_proximo_no_adjacencia(No_adjacencia* proximo_no_adjacencia);
        friend class ListaAdjacencia;
};
#endif