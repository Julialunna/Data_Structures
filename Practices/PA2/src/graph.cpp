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
        no_atual = no_atual->get_proximo_no_adjacencia();
    }
    return quant_vertices;
}
int Grafo::QuantidadeArestas(){
    No_adjacencia* vertice_atual = this->vertices.get_cabeca()->get_proximo_no_adjacencia();
    int quant_arestas = 0;
    while(vertice_atual!=nullptr){
        No* no_atual = vertice_atual->get_lista()->get_cabeca()->get_proximo_no();
        while(no_atual !=nullptr){
            quant_arestas++;
            no_atual = no_atual->get_proximo_no();
        }
        vertice_atual = vertice_atual->get_proximo_no_adjacencia();
    }
    return quant_arestas / 2;
}

int Grafo::GrauMinimo(){
    No_adjacencia* vertice_atual = this->vertices.get_cabeca()->get_proximo_no_adjacencia();
    int menor_grau = vertice_atual->get_lista()->get_tamanho();
    while(vertice_atual!=nullptr){
        if(vertice_atual->get_lista()->get_tamanho() < menor_grau){
            menor_grau = vertice_atual->get_lista()->get_tamanho();
        }
        vertice_atual = vertice_atual->get_proximo_no_adjacencia();
    }
    return menor_grau;

}
int Grafo::GrauMaximo(){
    No_adjacencia* vertice_atual = this->vertices.get_cabeca()->get_proximo_no_adjacencia();
    int maior_grau = vertice_atual->get_lista()->get_tamanho();
    while(vertice_atual!=nullptr){
        if(vertice_atual->get_lista()->get_tamanho() > maior_grau){
            maior_grau = vertice_atual->get_lista()->get_tamanho();
        }
        vertice_atual = vertice_atual->get_proximo_no_adjacencia();
    }
    return maior_grau;
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
