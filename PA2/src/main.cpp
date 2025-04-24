#include "graph.hpp"
#include <cstring>
#include <iostream>
int main(int argc, char **argv){
    char* comando = argv[1];
    int num_vertices = 0, num_vizinhos = 0;
    Grafo grafo_entrada;
    std::cin>>num_vertices;
    for (int i =1; i<=num_vertices;i++){
        grafo_entrada.InsereVertice();
    }

    for(int i=1; i<=num_vertices;i++){
        std::cin>>num_vizinhos;
        for(int j=0;j<num_vizinhos;j++){
            int vizinho = 0;
            std::cin>>vizinho;
            grafo_entrada.InsereAresta(i, vizinho);
        }
    }

    
    if(std::strcmp(comando, "-d") == 0){
        std::cout<<grafo_entrada.QuantidadeVertices()<<std::endl;
        
    }else if(std::strcmp(comando, "-n") == 0){
        for(int i=1;i<=num_vertices;i++){
            grafo_entrada.ImprimeVizinhos(i);

        }
    }else if(std::strcmp(comando, "-k") == 0){

    }
}