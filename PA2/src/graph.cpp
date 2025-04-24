#include "graph.hpp"
#include "list.hpp"
#include <iostream>

Grafo::Grafo(){
}
Grafo::~Grafo(){
}

void Grafo::InsereVertice(){
    this->vertices.insere_final();
}
void Grafo::InsereAresta(int v, int w){
    No_adjacencia *no_atual;
    no_atual = this->vertices.posiciona(v, true);
    no_atual->get_lista()->insere_final(w);
}

int Grafo::QuantidadeVertices(){
    int quant_vertices = 0;
    No_adjacencia* no_atual = this->vertices.get_cabeca()->get_proximo_no_adjacencia();
    while(no_atual!=nullptr){
        quant_vertices++;
    }
    return quant_vertices;
}
int Grafo::QuantidadeArestas(){


}

int Grafo::GrauMinimo(){

}
int Grafo::GrauMaximo(){

}

void Grafo::ImprimeVizinhos(int v){
    No_adjacencia *no_adjacencia_atual;
    no_adjacencia_atual = this->vertices.posiciona(v, true);
    Lista* lista_a_imprimir = no_adjacencia_atual->get_lista();
    No* no_a_imprimir = lista_a_imprimir->get_cabeca()->get_proximo_no();
    while(no_a_imprimir!=nullptr){
        std::cout<<no_a_imprimir->get_valor()<<std::ends;
        no_a_imprimir = no_a_imprimir->get_proximo_no();
        if(no_a_imprimir!=nullptr){
            std::cout<<" "<<std::ends;  
        }else{
            std::cout<<std::endl;
        }
    }
    no_adjacencia_atual = no_adjacencia_atual->get_proximo_no_adjacencia();
    
}
