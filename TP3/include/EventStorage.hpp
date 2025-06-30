#ifndef EVENTSTORAGE_HPP
#define EVENTSTORAGE_HPP

#include <string>
struct Event{
    int time = 0;
    std::string eventType = "";
    int packageId = -1;
    std::string sender = "";
    std::string recipient = "";
    int warehouseOrigin = -1;
    int warehouseDestination = -1;
    int destinationSection = -1;

};
class EventStorage{
    private:
    Event* events;
    int currentSize;
    int maxSize;
    public:
    EventStorage();
    ~EventStorage();
    void addEvent(Event new_event);
    void increaseStorage();
    int getCurrentSize();
    Event getEvent(int i);
    void printEvent(Event& e);
};
#endif

