#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP
#include "Stack.hpp"
#include "List.hpp"
#include "Package.hpp" 
 
class Warehouse{
    private:
    int id;
    int num_of_sections;
    int* index_section_mapping;
    Stack<Package>*sections_packages;
    public:
    bool operator==(const int& other_id) const {
        return this->id == other_id;
    }
    Warehouse();
    ~Warehouse();
    void set_id(int id);
    int get_id();
    void Store_package(Package &package, int section);
    Package& Retrieve_package(int section);
    int get_num_sections();
    int find_section_index(int section);
    void define_sections(int num_sections, List<int>* sections);
    int* get_index_section_mapping();
};
#endif