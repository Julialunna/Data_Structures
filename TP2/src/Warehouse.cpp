#include "Warehouse.hpp"
Warehouse::Warehouse(int id, int num_sections){
    this->id = id;
    this->num_of_sections = num_sections;
    this->sections_packages = new Stack<Package>[this->num_of_sections];
}
Warehouse::Warehouse() : id(0), num_of_sections(0), sections_packages(nullptr) {}

int Warehouse::get_num_sections(){
    return this->num_of_sections;
}

// Warehouse::~Warehouse(){

// }
void Warehouse::Store_package(Package package, int section){

}
void Warehouse::Retrieve_packages(int num_packages){

}
