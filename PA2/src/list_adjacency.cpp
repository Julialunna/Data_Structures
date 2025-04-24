#include <iostream>
#include "list_adjacency.hpp"
#include "list.hpp"

#include <iostream>
No_adjacencia::No_adjacencia(){
    this->lista_adjacencia = new Lista();
    this->proximo_no = nullptr;
}

Lista* No_adjacencia::get_lista(){
    return this->lista_adjacencia;
}
void No_adjacencia::set_lista(Lista* lista_adjacencia_no){
    this->lista_adjacencia = lista_adjacencia_no;
}
No_adjacencia* No_adjacencia::get_proximo_no_adjacencia(){
    return this->proximo_no;
}
void No_adjacencia::set_proximo_no_adjacencia(No_adjacencia* proximo_no_adjacencia){
    this->proximo_no = proximo_no_adjacencia;
}

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
void ListaAdjacencia::insere_final(){
    No_adjacencia *novo_no = new No_adjacencia();
    this->ultimo->set_proximo_no_adjacencia(novo_no);
    this->ultimo = novo_no;
    this->tamanho++;
}
No_adjacencia* ListaAdjacencia::get_cabeca(){
    return this->cabeca;
}
No_adjacencia* ListaAdjacencia::get_ultimo(){
    return this->ultimo;
}

No_adjacencia* ListaAdjacencia::posiciona(int pos, bool antes){
    No_adjacencia *no_atual;
    if(pos > this->tamanho || pos <= 0){
        throw "Erro posicao invalida";
    }
    
    no_atual = this->cabeca;
    
    for(int i =0; i<pos;i++){
        no_atual = no_atual->get_proximo_no_adjacencia();
    }

    if(antes){
        return no_atual;
    }else{
        return no_atual->get_proximo_no_adjacencia();
    }
}