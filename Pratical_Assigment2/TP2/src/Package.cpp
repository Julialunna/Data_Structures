#include "Package.hpp"


Package::Package()
    : id(-1)
    , state(1)
    , warehouse_origin_id(-1)
    , warehouse_destination_id(-1)
    , storage_time(0)
  {}

Package::Package(int id, int warehouse_origin_id, int warehouse_destination_id){
    this->id = id;
    this->state = 1;
    this->warehouse_origin_id = warehouse_origin_id;
    this->warehouse_destination_id = warehouse_destination_id;
}
//getters and setters
void Package::set_arrival_time(int time){
    this->arrival_time = time;
}
int Package::get_arrival_time(){
    return this->arrival_time;
}
int Package::get_id(){
    return this->id;
}
void Package::set_id(int new_id){
    this->id = new_id;
}
int Package::get_state(){
    return this->state;
}
void Package::set_state(int updated_state){
    this->state = updated_state;
}
void Package::set_warehouse_origin_id(int id){
    this->warehouse_origin_id =id;
}
int Package::get_warehouse_origin_id(){
    return this->warehouse_origin_id;
}
void Package::set_warehouse_destination_id(int id){
    this->warehouse_destination_id = id;
}

int Package::get_warehouse_destination_id(){
    return this->warehouse_destination_id;
}

//calculates route considering breadth first search
void Package::calculate_route(Graph<int>& warehouses){
   this->route = warehouses.BreadthFirstSearch(
        this->warehouse_origin_id,
        this->warehouse_destination_id
    );
}

List<int>* Package::get_route(){
    return &this->route;
}

void Package::set_last_arrival(int time){
    this->last_arrival = time;
}
int Package::get_storage_time(){
    return this->storage_time;
}
void Package::increase_storage_time(int time){
    int increase = time - this->last_arrival;
    this->storage_time+=increase; 
}