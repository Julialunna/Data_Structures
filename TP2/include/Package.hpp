#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "List.hpp"
#include "Graph.hpp"
/*
POSSIBLE STATES AND THEIR MEANINGS
state 1: Not posted
state 2: Staggered arrival at a warehouse
state 3: Arrived at a warehouse but not stored
state 4: Stored in a warehouse
state 5: Allocated for transportation
state 6: Delivered
 */

class Package{
    private:
    int id;
    int state;
    int storage_time;
    int transport_time;
    int warehouse_origin_id;
    int warehouse_destination_id;
    List<int> route;
    public:
    Package();
    Package(int id, int warehouse_origin_id, int warehouse_destination_id);
    int get_id();
    int get_state();
    void set_state(int state);
    void increase_storage_time(int increase);
    void increase_transport_time(int increase);
    bool operator==(const int& other_id) const {
        return this->id == other_id;
    }
    int get_warehouse_origin_id();
    int get_warehouse_destination_id();
    void calculate_route(Graph<int>& warehouses);
    List<int>* get_route();
    
};
#endif