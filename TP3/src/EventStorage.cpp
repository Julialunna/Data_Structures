#include "EventStorage.hpp"
#include <iostream>
#include <iomanip>
const int min_size = 10;

EventStorage::EventStorage()
{
    // defining initial size as 10
    this->events = new Event[min_size];
    this->currentSize = 0;
    this->maxSize = min_size;
}

EventStorage::~EventStorage()
{
    delete[] this->events;
}

int EventStorage::getCurrentSize(){
    return this->currentSize;
}

//increases storage if array Event gets full
void EventStorage::increaseStorage()
{
    // incresing 2 times events array size
    Event *aux = new Event[this->maxSize * 2];
    if (!aux)
    {
        std::cerr << "Error: nao foi possivel adicionar evento\n";
    }
    else
    {
        for (int i = 0; i < this->maxSize; i++)
        {
            aux[i] = this->events[i];
        }
        delete[] this->events;
        this->events = aux;
        this->maxSize = this->maxSize * 2;
    }
}

//add event and guarantees they are ordered by time
void EventStorage::addEvent(Event e)
{
    //check if there is space to add event
    if (this->currentSize == this->maxSize)
    {
        this->increaseStorage();
    }
    this->events[this->currentSize] = e;
    
    this->currentSize++;
}

Event EventStorage::getEvent(int i){
    return this->events[i];
}

//print event accordingly to its type
void EventStorage::printEvent(Event& e){
    std::cout << std::setfill('0')
              << std::setw(7) << e.time   
              << std::setfill(' ')        
              << " EV " 
              << e.eventType;

    if (e.eventType == "RG") {
        std::cout << ' '
                  << std::setfill('0') << std::setw(3) << e.packageId
                  << std::setfill(' ') << ' '
                  << e.sender << ' '
                  << e.recipient << ' '
                  << std::setfill('0') << std::setw(3) << e.warehouseOrigin
                  << ' ' << std::setw(3) << e.warehouseDestination;
    }
    else if (e.eventType == "AR"
          || e.eventType == "RM"
          || e.eventType == "UR")
    {
        std::cout << ' '
                  << std::setfill('0') << std::setw(3) << e.packageId
                  << ' ' << std::setw(3) << e.warehouseDestination
                  << ' ' << std::setw(3) << e.destinationSection;
    }
    else if (e.eventType == "TR") {
        std::cout << ' '
                  << std::setfill('0') << std::setw(3) << e.packageId
                  << ' ' << std::setw(3) << e.warehouseOrigin
                  << ' ' << std::setw(3) << e.warehouseDestination;
    }
    else if (e.eventType == "EN") {
        std::cout << ' '
                  << std::setfill('0') << std::setw(3) << e.packageId
                  << ' ' << std::setw(3) << e.warehouseDestination;
    }
    else {
        std::cout<<e.packageId<<std::endl;
        std::cerr << "\nError: tipo de evento inválido ("
                  << e.eventType << ")\n";
        return;
    }
    std::cout << '\n';
}
