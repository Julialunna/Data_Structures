#include "node_adjacency.hpp"

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