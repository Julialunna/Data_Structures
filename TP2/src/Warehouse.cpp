
#include "Warehouse.hpp"

void Warehouse::define_sections(int num_sections, List<int>*sections){
    this->num_of_sections = num_sections;
    this->sections_packages = new Stack<Package>[this->num_of_sections];
    //mapping correspondency of index on stack to neighors warehouses ids
    this->index_section_mapping =  new int[this->num_of_sections];
    for(int i =1;i<=num_of_sections;i++){
        this->index_section_mapping[i-1]= sections->getItem(i);
    }
}
void Warehouse::set_id(int id){
    this->id = id;
}
int Warehouse::get_id(){
    return this->id;
}
Warehouse::Warehouse() : id(0), num_of_sections(0), sections_packages(nullptr) {}

int Warehouse::get_num_sections(){
    return this->num_of_sections;
}

Warehouse::~Warehouse(){
    delete[] this->sections_packages;
    delete[] this->index_section_mapping;
}

//define the index on sections_packages correspondent to the section id
int Warehouse::find_section_index(int section){
    int found_section = -1;
    for(int i =0;i<this->num_of_sections;i++){
        if(this->index_section_mapping[i]==section){
            
            found_section = i;
        }
    }
    return found_section;
}

//store package at section
void Warehouse::Store_package(Package &package, int section){
    int section_index = this->find_section_index(section);
    this->sections_packages[section_index].pile(package);
    //CONFERIR!
    package.set_state(3);
    
}

//get package from section stack
Package& Warehouse::Retrieve_package(int section){
    int section_index = this->find_section_index(section);
    if(this->sections_packages[section_index].get_size()){
        throw "Empty section";
    }
    return this->sections_packages[section_index].unstack();
}
