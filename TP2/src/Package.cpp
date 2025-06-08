#include "Package.hpp"

Package::Package(int id, int warehouse_origin_id, int warehouse_destination_id){
    this->id = id;
    //conferir
    this->state = 1;
    this->storage_time = 0;
    this->transport_time = 0;
    this->warehouse_origin_id = warehouse_origin_id;
    this->warehouse_destination_id = warehouse_destination_id;
}
int Package::get_id(){
    return this->id;
}
int Package::get_state(){
    return this->state;
}
void Package::set_state(int state){
    this->state = state;
}
void Package::increase_storage_time(int increase){
    this->storage_time += increase;
}
void Package::increase_transport_time(int increase){
    this->transport_time += increase;
}
int Package::get_warehouse_origin_id(){
    return this->warehouse_origin_id;
}
int Package::get_warehouse_destination_id(){
    return this->warehouse_destination_id;
}