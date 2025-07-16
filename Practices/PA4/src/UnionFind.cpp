#include "UnionFind.hpp"
#include <iostream>
UnionFind::UnionFind(int quantidade_subconjuntos){
    this->tamanho = quantidade_subconjuntos;
    this->subconjuntos = new Subconjunto[quantidade_subconjuntos];
}
UnionFind::~UnionFind(){
    delete[] subconjuntos;
}
void UnionFind::Make(int x){
    this->subconjuntos[x].representante =x;
    this->subconjuntos[x].rank = 0;
}
int UnionFind::Find(int x){
    while(this->subconjuntos[x].representante != x){
        x = this->subconjuntos[x].representante;
    }
    return x;
}
void UnionFind::Union(int x, int y){
    int raiz_x = Find(x);
    int raiz_y = Find(y);
    if(raiz_x != raiz_y){
        if(this->subconjuntos[raiz_x].rank < this->subconjuntos[raiz_y].rank){
            this->subconjuntos[raiz_x].representante = subconjuntos[raiz_y].representante;
        }else if(this->subconjuntos[raiz_x].rank > this->subconjuntos[raiz_y].rank){
            this->subconjuntos[raiz_y].representante = subconjuntos[raiz_x].representante;
        }else{
            this->subconjuntos[raiz_x].representante = this->subconjuntos[raiz_y].representante;
            this->subconjuntos[raiz_x].rank++;
        }
    }
}