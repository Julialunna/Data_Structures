#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Graph.hpp"
#include "Warehouse.hpp"
#include "Scheduler.hpp"

int main(int argc, char*argv[]){
    
    std::string file_name, line;
    
    //opening file
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

    int transport_capacity = 0, transport_latency = 0, transport_break = 0, 
    removal_cost = 0, num_warehouses = 0, weight = 0;
    
    file >> transport_capacity;
    file >> transport_latency;
    file>> transport_break;
    file >> removal_cost;
    file >> num_warehouses;

    Warehouse *warehouses = new Warehouse[num_warehouses];
    Scheduler scheduler (transport_capacity, transport_latency, transport_break, removal_cost);

    Event evento;
    //reading warehouses topology 
    Graph<int> graph_warehouses(num_warehouses);
    for(int i =0; i<num_warehouses; i++){
        for(int j = 0; j<num_warehouses; j++){
            file >> weight;
            if(weight != 0){
                graph_warehouses.InsertEdge(i, j, weight);
            }
        }
        warehouses[i].set_id(i);
        //define section at each warehouse considering the graph topology
        warehouses[i].define_sections(graph_warehouses.FindNeighbors(i)->getSize(), graph_warehouses.FindNeighbors(i));
    }

    int num_packages = 0;
    file >> num_packages;
    Package *packages = new Package[num_packages];
    std::string name;

    //getting packages informations
    for(int i = 0; i<num_packages;i++){
        int entry = 0, id= 0, origin_warehouse = 0, destination_warehouse = 0;
        file >> entry;
        packages[i].set_arrival_time(entry);
        file >> name;
        file >> id;
        packages[i].set_id(i);
        file >> name;
        file >> origin_warehouse;
        packages[i].set_warehouse_origin_id(origin_warehouse);
        file >> name;
        file >> destination_warehouse;
        packages[i].set_warehouse_destination_id(destination_warehouse);
        packages[i].set_state(1);
        packages[i].calculate_route(graph_warehouses);
    }

    for(int i=0;i<num_packages;i++){
        int transport_time_dijkstra = packages[i].calculate_tranport_time(graph_warehouses);
        int transport_time_bfs = packages[i].calculate_transport_time_bfs(graph_warehouses);
        std::cout<<"Pacote "<<i<<":\n";
        std::cout<<"Tempo usando Dijkstra: " << transport_time_dijkstra << std::endl;
        std::cout<<"Tempo usando BFS: " << transport_time_bfs << std::endl;
    }
    //simulating the deliveries 
    scheduler.simulate_deliveries(num_packages, packages, num_warehouses, warehouses);



    delete[] warehouses;
    delete[] packages;
    return 0;
}

