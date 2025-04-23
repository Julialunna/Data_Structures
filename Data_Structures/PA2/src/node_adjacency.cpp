#include "node_adjacency.hpp"

#include <iostream>
No_adjacencia::No_adjacencia(){
    this->num_vertice = -1;
    this->lista_adjacencia = nullptr;
    this->proximo_no = nullptr;
}
No_adjacencia::No_adjacencia(int num_vertice){
    this->num_vertice = num_vertice;
    this->lista_adjacencia = nullptr;
    this->proximo_no = nullptr;
}
Lista* No_adjacencia::get_lista(){
    return this->lista_adjacencia;
}
void No_adjacencia::set_lista(Lista* lista_adjacencia_no){
    this->lista_adjacencia = lista_adjacencia_no;
}
int No_adjacencia::get_num_vertice(){
    return this->num_vertice;
}
void No_adjacencia::set_num_vertice(int num_vertice_no){
    this->num_vertice = num_vertice_no;
}
No_adjacencia* No_adjacencia::get_proximo_no_adjacencia(){
    return this->proximo_no;
}
void No_adjacencia::set_proximo_no_adjacencia(No_adjacencia* proximo_no_adjacencia){
    this->proximo_no = proximo_no_adjacencia;
}