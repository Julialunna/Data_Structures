#include <iostream>
#include "list_adjacency.hpp"
#include "node_adjacency.hpp"
ListaAdjacencia::ListaAdjacencia(){
    this->cabeca = new No_adjacencia();
    this->ultimo = this->cabeca;
    this->tamanho = 0;
}
ListaAdjacencia::~ListaAdjacencia(){
    No_adjacencia* no_atual = this->cabeca;
    while(no_atual != nullptr){
        No_adjacencia* no_a_deletar = no_atual;
        no_atual = no_atual->get_proximo_no_adjacencia();
        delete no_a_deletar;
    }
    this->tamanho = 0;
}
void ListaAdjacencia::insere_final(int valor_novo_no_adjacencia){
    No_adjacencia *novo_no = new No_adjacencia(valor_novo_no_adjacencia);
    this->ultimo->set_proximo_no_adjacencia(novo_no);
    this->ultimo = novo_no;
    this->tamanho++;
}