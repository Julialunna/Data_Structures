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
    return new_event;
}
void Scheduler::initialize(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses){
    for(int i =0;i< num_warehouses;i++){
        std::cout<<"A \n";
        for(int j = 0;j<warehouses->get_num_sections(); j++){
            this->create_transport_event(0, warehouses[i].get_id(), warehouses[i].get_index_section_mapping()[j]);
        }
    }
    for(int i =0;i<num_packages;i++){
        this->create_package_event(packages[i].get_id(), packages[i].get_arrival_time());
        packages[i].set_state(2);
    }
}
void Scheduler::remove_next_event(){

}
void Scheduler::end(){

}
void Scheduler::simulate_deliveries(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses){
    int current_time = 0;
    this->initialize(num_packages, packages, num_warehouses, warehouses);
}
