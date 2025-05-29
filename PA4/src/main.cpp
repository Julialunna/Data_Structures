#include "heap.hpp"
#include "UnionFind.hpp"
#include <iostream>
int main(){
    int num_arestas = 0, num_vertices = 0;
    std::cin>>num_vertices>>num_arestas;

    Heap min_heap(num_arestas);
    UnionFind union_find(num_vertices);
    s_edge* arestas = new s_edge[num_arestas];

    int vertice1=0, vertice2=0, custos=0;
    for(int i =0; i< num_arestas;i++){
        std::cin>>vertice1>>vertice2>>custos;
        arestas[i].custo = custos;
        arestas[i].u = vertice1;
        arestas[i].v = vertice2;
        min_heap.Insert(arestas[i]);
    }
    int custo_total =0, unioes = 0;
    for(int i =0;i<num_vertices;i++){
        union_find.Make(i);
    } 
    for(int i=0;i<num_arestas;i++){
        //para escolhermos arestas de menor peso
        s_edge aresta_retirada = min_heap.Remove();
        //para verificar se não terá ciclo
        if(union_find.Find(aresta_retirada.u)!=union_find.Find(aresta_retirada.v)){
            union_find.Union(aresta_retirada.u, aresta_retirada.v);
            custo_total+=aresta_retirada.custo;
            unioes++;
        }
        if(unioes == num_vertices - 1){
            break;
        }
    }
    std::cout<<custo_total<<std::endl;

}