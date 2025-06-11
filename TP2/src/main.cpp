#include <iostream>
#include <fstream>
#include <string>
#include "Graph.hpp"
#include "Warehouse.hpp"
#include "Scheduler.hpp"

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

    int transport_capacity = 0, transport_latency = 0, transport_break = 0, 
    removal_cost = 0, num_warehouses = 0, is_connected = 0;
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
            file >> is_connected;
            if(is_connected == 1){
                graph_warehouses.InsertEdge(i, j);
            }
        }
        warehouses[i].set_id(i);
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
        packages[i].set_id(id);
        file >> name;
        file >> origin_warehouse;
        packages[i].set_warehouse_origin_id(origin_warehouse);
        file >> name;
        file >> destination_warehouse;
        packages[i].set_warehouse_destination_id(destination_warehouse);
        packages[i].set_state(1);
        packages[i].calculate_route(graph_warehouses);
    }
    for(int i = 0; i<num_packages;i++){
    
        std::cout<<packages[i].get_id()<<" "<<packages[i].get_arrival_time()<<" "<<packages[i].get_warehouse_origin_id()<<" "<<packages[i].get_warehouse_destination_id()<<"\n"; 
        packages[i].get_route()->print();
        
    }
    scheduler.simulate_deliveries(num_packages, packages, num_warehouses, warehouses);
    std::cout<<"B1\n";
    delete[] warehouses;
    delete[] packages;
    return 0;
}

