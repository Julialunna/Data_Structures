#ifndef LIST_ADJACENCY_HPP
#define LIST_ADJACENCY_HPP
#include "node_adjacency.hpp"
class ListaAdjacencia{
    private:
        No_adjacencia* cabeca;
        No_adjacencia* ultimo;
        int tamanho;
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();
        void insere_final(int valor_novo_no_adjacencia);
};
#endif