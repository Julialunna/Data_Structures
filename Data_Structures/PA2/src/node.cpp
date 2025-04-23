#include<iostream>
#include "node.hpp"

No::No(): valor(-1), proximo(nullptr){}

No::No(int valor_no): valor(valor_no), proximo(nullptr){}

int No::get_valor(){
    return this->valor;
}
void No::set_valor(int valor_no){
    this->valor = valor_no;
}
No* No::get_proximo_no(){
    return this->proximo;
}
void No::set_proximo_no(No* proximo_no){
    this->proximo = proximo_no;
}