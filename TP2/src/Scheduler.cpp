#include "Scheduler.hpp"
#include <string>
#include <iomanip>
#include <sstream>
#define TIME_SIZE 6
#define WAREHOUSE_ID_SIZE 3

Scheduler::Scheduler(int transport_capacity_received,int transport_latency_received, int transport_break_received, int removal_cost_received)
    : transport_capacity(transport_capacity_received)
    , transport_latency(transport_latency_received)
    , transport_break(transport_break_received)
    , removal_cost(removal_cost_received)
{}

Event Scheduler::create_transport_event(int time, int warehouse_origin_id, int warehouse_destination_id){
    Event new_event;
    std::ostringstream key;
    key << std::setfill('0') << std::setw(6) << time;
    key << std::setfill('0') << std::setw(3) << warehouse_origin_id;
    key << std::setfill('0') << std::setw(3) << warehouse_destination_id;
    key << 2; // type 2 because it is a transport event
    std::string new_key = key.str();
    new_event.event_key = new_key;
    this->events.Insert(new_event);
    return new_event;
}
Event Scheduler::create_package_event(int package_id, int time){
    Event new_event;
    std::ostringstream key;
    key << std::setfill('0') << std::setw(6) << time;
    key << std::setfill('0') << std::setw(6) << package_id;
    key << 1; // type 1 because it is a package event
    std::string new_key = key.str();
    new_event.event_key = new_key;
    this->events.Insert(new_event);
    return new_event;
}
void Scheduler::initialize(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses){
    for(int i =0;i< num_warehouses;i++){
        for(int j = 0;j<warehouses->get_num_sections(); j++){
            this->create_transport_event(0, warehouses[i].get_id(), warehouses[i].get_index_section_mapping()[j]);
        }
    }
    for(int i =0;i<num_packages;i++){
        this->create_package_event(packages[i].get_id(), packages[i].get_arrival_time());
        packages[i].set_state(2);
    }
}

void Scheduler::execute_transport_event(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses, Event event){

}
void Scheduler::execute_package_event(Package* packages, Warehouse* warehouses, Event event, int current_time){
    int package_id = std::stoi(event.event_key.substr(6, 6));
    if(packages[package_id].get_state() == 2){
        std::cout<<package_id<<std::endl;
        packages[package_id].get_route()->print();
        int warehouse_arrival_id = packages[package_id].get_route()->removeBeginning();
        int section = packages[package_id].get_route()->getItem(1);
        int section_index = warehouses[warehouse_arrival_id].find_section_index(section); 
        if(section_index == -1){
            throw "No section to store package";
        }
        warehouses[warehouse_arrival_id].Store_package(packages[package_id], section_index);

        std::cout
        << std::setfill('0') << std::setw(7) << current_time << " "
        << "pacote " << std::setw(3) << package_id << " "
        << "armazenado em " << std::setw(3) << warehouse_arrival_id << " "
        << "na secao " << std::setw(3) << section
        << std::endl;
    }
    
    
}
void Scheduler::remove_next_event(){

}
void Scheduler::end(){

}

bool Scheduler::check_empty_sections(int num_warehouses, Warehouse* warehouses){
    for(int i =0;i< num_warehouses;i++){
        for(int j = 0;j<warehouses->get_num_sections(); j++){
            if(!warehouses[i].get_section()[j].empty()){
                return false;
            }
        }
    }
    return true;
}
void Scheduler::simulate_deliveries(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses){
    int current_time = 0;
    this->initialize(num_packages, packages, num_warehouses, warehouses);
    while(!this->events.Empty()){
        std::cout<<"A\n";
        Event next_event = this->events.Remove();
        std::cout<<"Evento retirado"<<next_event.event_key<<std::endl;
        current_time = std::stoi(next_event.event_key.substr(0, 6));
        if(std::stoi(next_event.event_key.substr(12, 1)) == 1){

            this->execute_package_event( packages,  warehouses, next_event, current_time);
        }else if(std::stoi(next_event.event_key.substr(12, 1)) == 2){
            this->execute_transport_event(num_packages, packages, num_warehouses, warehouses, next_event);
        }
    }
    std::cout<<"B0\n";
    // }while(!this->events.Empty() && !check_empty_sections(num_warehouses, warehouses)) ;
}
