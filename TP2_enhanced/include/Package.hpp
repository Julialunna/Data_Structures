#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include "List.hpp"
#include "Graph.hpp"
/*
POSSIBLE STATES AND THEIR MEANINGS
state 1: Not posted
state 2: Staggered arrival at a warehouse
state 3: Stored in section associated to next destine warehouse
state 4: removed from section to transport
state 5: Delivered
*/

class Package{
    private:
    int id;
    int arrival_time;
    int state;
    int warehouse_origin_id;
    int warehouse_destination_id;
    int storage_time;
    int transport_time;
    List<int> route;
    int last_arrival;
    public:
    Package();
    Package(int id, int warehouse_origin_id, int warehouse_destination_id);
    void set_id(int new_id);
    int get_id();
    void set_arrival_time(int time);
    int get_arrival_time();
    int get_state();
    void set_state(int updated_state);
    void set_last_arrival(int time);
    int get_storage_time();
    void increase_storage_time(int time);
    int get_warehouse_origin_id();
    void set_warehouse_origin_id(int id);
    int get_warehouse_destination_id();
    void set_warehouse_destination_id(int id);
    int calculate_tranport_time(Graph<int>& warehouses);
    int calculate_transport_time_bfs(Graph<int>& warehouses);
    bool operator==(const int& other_id) const {
        return this->id == other_id;
    }
    void calculate_route(Graph<int>& warehouses);
    List<int>* get_route();
};
#endif

