#include "Warehouse.hpp"
#include "Package.hpp"
#include "MinHeap.hpp"
#include <string>
#define KEY_SIZE 13

struct Event{
    std::string event_key;

    bool operator<(const Event& other) const {
        if(event_key.compare(other.event_key) < 0){
            return true;
        }else{
            return false;
        }
    }
    bool operator>(const Event& other) const {
        if(event_key.compare(other.event_key) > 0){
            return true;
        }else{
            return false;
        }
    }
    bool operator==(const Event& other) const {
        if(event_key.compare(other.event_key) == 0){
            return true;
        }else{
            return false;
        }
    }
};
inline std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << e.event_key;
    return os;
}

class Scheduler{
    private:
    int transport_capacity;
    int transport_latency;
    int  transport_break;
    int removal_cost;
    MinHeap<Event> events;
    public:
    Scheduler(int transport_capacity_received,int transport_latency_received, int transport_break_received, int removal_cost_received);
    Event create_transport_event( int time, int warehouse_origin_id, int warehouse_destination_id);
    Event create_package_event(int package_id, int time);
    void initialize_arrival_events(int num_packages, Package* packages);
    void initialize_transport_events(int num_warehouses, Warehouse* warehouses, int initial_time);
    void execute_transport_event(Package* packages, Warehouse* warehouses, int warehouse_origin_id, int warehouse_destination_id, int current_time, int *num_restores);
    void execute_arrival_event( Package* packages, Warehouse* warehouses, Event event, int current_time);
    bool is_all_packages_delivered(int num_packages, Package* packages);
    void simulate_deliveries(int num_packages, Package* packages, int num_warehouses, Warehouse* warehouses);

};