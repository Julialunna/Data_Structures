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
    Event create_arrival_event(int package_id, int time);
    void initialize();
    void remove_next_event();
    void end();
    void simulate_deliveries(Package* packages, Warehouse* warehouses);

};