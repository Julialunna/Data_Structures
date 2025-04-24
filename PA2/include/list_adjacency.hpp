#ifndef LIST_ADJACENCY_HPP
#define LIST_ADJACENCY_HPP
#include "list.hpp"

class ListaAdjacencia;

class No_adjacencia{
    private:   
        Lista* lista_adjacencia;
        No_adjacencia* proximo_no;
    public:
        No_adjacencia();
        Lista* get_lista();
        void set_lista(Lista* lista_adjacencia_no);
        int get_num_vertice();
        void set_num_vertice(int num_vertice_no);
        No_adjacencia* get_proximo_no_adjacencia();
        void set_proximo_no_adjacencia(No_adjacencia* proximo_no_adjacencia);
        friend class ListaAdjacencia;
};

class ListaAdjacencia{
    private:
        No_adjacencia* cabeca;
        No_adjacencia* ultimo;
        int tamanho;
    public:
        ListaAdjacencia();
        ~ListaAdjacencia();
        void insere_final();
        No_adjacencia* get_cabeca();
        No_adjacencia* get_ultimo();
        No_adjacencia* posiciona(int pos, bool antes);
};
#endif