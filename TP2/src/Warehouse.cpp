#include "Warehouse.hpp"

Warehouse::Warehouse() : id(0), num_of_sections(0), sections_packages(nullptr) {}
Warehouse::~Warehouse(){
    
    if (this->sections_packages != nullptr) {
        delete[] this->sections_packages;
    }
    if (this->index_section_mapping != nullptr) {
        delete[] this->index_section_mapping;
    }
}

//getters and setters
void Warehouse::set_id(int id){
    this->id = id;
}
int Warehouse::get_id(){
    return this->id;
}

int Warehouse::get_num_sections(){
    return this->num_of_sections;
}

int* Warehouse::get_index_section_mapping(){
    return this->index_section_mapping;
}

Stack<int>* Warehouse::get_section(){
    return this->sections_packages;
}

//define wich sections the warehouse will have
void Warehouse::define_sections(int num_sections, List<int>*sections){
    this->num_of_sections = num_sections;
    this->sections_packages = new Stack<int>[this->num_of_sections]();

    //mapping correspondency of index on stack to neighors warehouses ids
    this->index_section_mapping =  new int[this->num_of_sections];
    
    for(int i =0;i<num_of_sections;i++){
        this->index_section_mapping[i]= sections->getItem(i+1);
    }
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


//checks is certain section is empty
bool Warehouse::is_section_empty(int section){
    int section_index = this->find_section_index(section);
    if (section_index == -1) return true;
    return this->sections_packages[section_index].empty();
}

//store package at section
void Warehouse::Store_package(int package, int section){
    int section_index = this->find_section_index(section);
    if (section_index == -1) return;
    this->sections_packages[section_index].pile(package);
    
}

//get package from certain section 
int Warehouse::Retrieve_package(int section){
    int section_index = this->find_section_index(section);
    if (section_index == -1) return -1;
    if(this->sections_packages[section_index].get_size() == 0){
        std::cerr<<"Empty section"<<std::endl;
        return -1;
    }
    return this->sections_packages[section_index].unstack();
}
