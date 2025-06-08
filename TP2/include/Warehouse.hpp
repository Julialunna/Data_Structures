#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP
#include "Stack.hpp"
#include "Package.hpp"
class Warehouse{
    private:
    int id;
    int num_of_sections;
    //trocar para lista
    //ou vetor correspondency 
    Stack<Package>*sections_packages;
    public:
    bool operator==(const int& other_id) const {
        return this->id == other_id;
    }
    Warehouse(int id, int num_sections);
    Warehouse();
    void Store_package(Package package, int section);
    void Retrieve_packages(int num_packages);
    int get_num_sections();
};
#endif