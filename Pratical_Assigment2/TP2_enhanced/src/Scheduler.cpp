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

//create event key based on time and origin and destination warehouses
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

//create event key basend on time and package id
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

//create transport events to all possible transportations between warehouses considering their sections
void Scheduler::initialize_transport_events(int num_warehouses, Warehouse* warehouses, int initial_time){
    for(int i =0;i< num_warehouses;i++){
        for(int j = 0;j<warehouses[i].get_num_sections(); j++){
            this->create_transport_event(initial_time, warehouses[i].get_id(), warehouses[i].get_index_section_mapping()[j]);
        }
    }
}

//creates events for the arrival of packages at their source warehouses
void Scheduler::initialize_arrival_events(int num_packages, Package* packages){
    for(int i =0;i<num_packages;i++){
        this->create_package_event(packages[i].get_id(), packages[i].get_arrival_time());
        packages[i].set_state(2);
    }
}

//O(pacotes em seção)
void Scheduler::execute_transport_event(Package* packages, Warehouse* warehouses, int warehouse_origin_id, int warehouse_destination_id, int current_time, int* num_restores){
    int section_index = warehouses[warehouse_origin_id].find_section_index(warehouse_destination_id);
    Stack<int> aux;
    
    //if section is empty no need to execute transport
    if(warehouses[warehouse_origin_id].is_section_empty(warehouse_destination_id) == false){
        int num_packages_at_section = warehouses[warehouse_origin_id].get_section()[section_index].get_size();
        //removing packages from their section
        for(int i =0; i<num_packages_at_section;i++){
            int package_removed = warehouses[warehouse_origin_id].Retrieve_package(warehouse_destination_id);
            aux.pile(package_removed);
            current_time += this->removal_cost;
            packages[package_removed].increase_storage_time(current_time);
            std::cout
            << std::setfill('0') << std::setw(7) << current_time << " "
            << "pacote " << std::setw(3) << package_removed << " "
            << "removido de " << std::setw(3) << warehouse_origin_id << " "
            << "na secao " << std::setw(3) << warehouse_destination_id
            << std::endl;

        }
        
        int aux_size = aux.get_size();
        for(int i = 0;i<aux_size;i++){
            int package_removed = aux.unstack();
            //transports only the amount of packages that fit in the transport
            if(i<this->transport_capacity){
                std::cout
                << std::setfill('0') << std::setw(7) << current_time << " "
                << "pacote " << std::setw(3) << package_removed << " "
                << "em transito de " << std::setw(3) << warehouse_origin_id << " "
                << "para " << std::setw(3) << warehouse_destination_id
                << std::endl;

                //staggering package arrival
                packages[package_removed].set_state(2);
                this->create_package_event(package_removed, current_time+this->transport_latency);

            }else{
                //restore the leftover packages
                warehouses[warehouse_origin_id].Store_package(package_removed, warehouse_destination_id);
                std::cout
                << std::setfill('0') << std::setw(7) << current_time << " "
                << "pacote " << std::setw(3) << package_removed << " "
                << "rearmazenado em " << std::setw(3) << warehouse_origin_id<< " " 
                << "na secao " << std::setw(3) << warehouse_destination_id
                << std::endl;
                
                (*num_restores)++;
                packages[package_removed].set_last_arrival(current_time);
            }
        }
    }
    
}
//checks if all packages were delivered
bool Scheduler::is_all_packages_delivered(int num_packages, Package* packages){
    for(int i =0;i<num_packages;i++){
        if(packages[i].get_state()!=5){
            return false;
        }
    }
    return true;
}

//O(1)
//executes the arrival
void Scheduler::execute_arrival_event(Package* packages, Warehouse* warehouses, Event event, int current_time){
    int package_id = std::stoi(event.event_key.substr(6, 6));
    
    if(packages[package_id].get_state() == 2){

        int warehouse_arrival_id = packages[package_id].get_route()->removeBeginning();
        
        //if the arrival is on the destinatio print that package was delivered
        if(packages[package_id].get_warehouse_destination_id() == warehouse_arrival_id){
            packages[package_id].set_arrival_time(current_time);
            //set delivered state (5)
            packages[package_id].set_state(5);
            std::cout
            << std::setfill('0') << std::setw(7) << current_time << " "
            << "pacote " << std::setw(3) << package_id << " "
            << "entregue em " << std::setw(3) << warehouse_arrival_id
            << std::endl;
            
        }else{
            int section = packages[package_id].get_route()->getItem(1);
            int section_index = warehouses[warehouse_arrival_id].find_section_index(section); 
            if(section_index == -1){
                std::cerr<<"No section to store package"<<std::endl;
            }else{
                //set Stored in section associated to next destine warehouse state(3)
                packages[package_id].set_state(3);
                packages[package_id].set_last_arrival(current_time);
                warehouses[warehouse_arrival_id].Store_package(package_id, section);
                std::cout
                << std::setfill('0') << std::setw(7) << current_time << " "
                << "pacote " << std::setw(3) << package_id << " "
                << "armazenado em " << std::setw(3) << warehouse_arrival_id << " "
                << "na secao " << std::setw(3) << section
                << std::endl;
                

            }
        }

    }
    
}

//simulates deliveries of all packages
void Scheduler::simulate_deliveries(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses){
    int current_time = 0, num_restores = 0;
    this->initialize_arrival_events(num_packages, packages);
    Event next_event = this->events.Remove();

    //the initial time of the simulator is the time of the first package post, this way we can stagger the transports
    int initial_time = std::stoi(next_event.event_key.substr(0, 6));
    this->initialize_transport_events(num_warehouses, warehouses, initial_time+this->transport_break);
    int i =0;
    while(this->is_all_packages_delivered(num_packages, packages) == false){
        current_time = std::stoi(next_event.event_key.substr(0, 6));
        //if event key last digit is 1 it is a arrival event
        if(std::stoi(next_event.event_key.substr(12, 1)) == 1){
            this->execute_arrival_event( packages,  warehouses, next_event, current_time);

        }// if event key last digit is 2 it is a arrival event
        else if(std::stoi(next_event.event_key.substr(12, 1)) == 2){
            int warehouse_origin_id = std::stoi(next_event.event_key.substr(6, 3));
            int warehouse_destination_id = std::stoi(next_event.event_key.substr(9, 3));
            this->execute_transport_event(packages, warehouses,warehouse_origin_id , warehouse_destination_id, current_time, &num_restores);
            //scales next transport event if all packages aren't delivered yet
            if(this->is_all_packages_delivered(num_packages, packages) == false){
                this->create_transport_event(current_time + this->transport_break, warehouse_origin_id, warehouse_destination_id);
            }
        }
        next_event = this->events.Remove();
        i++;
    };

    
    
}

