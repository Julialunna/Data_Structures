// for(int i =1;i<=num_vertex;i++){
//     file >> num;
//     graph_warehouse.InsertVertex();
//     Warehouse new_warehouse(i, num);
//     warehouses.insertBeginning(new_warehouse);
// }
//List<Package> packages;
#include <iostream>
#include <fstream>
#include "List.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Graph.hpp"
#include "MinHeap.hpp"
#include "Warehouse.hpp"
int main(int argc, char*argv[]){
    
    std::string file_name, line;
    
    if (argc != 2) {
        std::cerr << "Erro: file name needed" << std::endl;
        return 1;
    }

   file_name = argv[1];

    std::ifstream file(file_name);
    
    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    int num_vertex = 0, num_packages = 0, destination = 0, origin =0;
    file >> num_vertex;
    file >> num_packages;
    file >> origin;
    file >> destination;
    Graph<int> graph_warehouse(num_vertex);
    List<Warehouse> warehouses;
    
    int neighbor_index = 0, num_neighbors;
    //reading graph
    for(int i =0;i<num_vertex;i++){
        file >> num_neighbors;
        for(int j=0;j<num_neighbors;j++){
            file >> neighbor_index;
            try{
                graph_warehouse.InsertEdge(i, neighbor_index, i, neighbor_index);
            }catch (const char* e) {
                std::cerr << e << "\n";
            }
        }
        graph_warehouse.PrintNeighbors(i);
        
    }
    List<int> path = graph_warehouse.BreadthFirstSearch(origin, destination);
    path.print();

    return 0;
}

