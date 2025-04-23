#include "graph.hpp"
#include <cstring>
#include <iostream>
int main(int argc, char **argv){
    char* comando = argv[1];
    Grafo grafo_entrada;
   
    if(std::strcmp(comando, "-d") == 0){
        std::cout<<comando<<std::endl;
    }else if(std::strcmp(comando, "-n") == 0){

    }else if(std::strcmp(comando, "-k") == 0){

    }
}