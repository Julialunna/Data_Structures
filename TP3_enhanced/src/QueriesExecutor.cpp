#include "QueriesExecutor.hpp"
#include <iostream>
#include <string>
#include <iomanip>
const int minSize = 10;
//constructor
QueriesExecutor::QueriesExecutor(){
    this->queries = new Query[minSize];
    this->maxNumQueries = minSize;
    this->numQueries = 0;
}
//destructor
QueriesExecutor::~QueriesExecutor(){
    delete[] this->queries;
}
//ncreases storage if Queries array gets full
void QueriesExecutor::increaseSize(){
    // incresing 2 times queries array size
    Query *aux = new Query[this->maxNumQueries * 2];
    if (!aux)
    
    
    {
        std::cerr << "Error: nao foi possivel adicionar evento\n";
    }
    else
    {
        for (int i = 0; i < this->maxNumQueries; i++)
        {
            aux[i] = this->queries[i];
        }
        delete[] this->queries;
        this->queries = aux;
        this->maxNumQueries = this->maxNumQueries * 2;
    }
}
//add query at queries array
void QueriesExecutor::addQuerie(Query new_query){
    if(this->numQueries == this->maxNumQueries){
        this->increaseSize();
    }
    this->queries[this->numQueries] = new_query;
    this->numQueries++;
    
}

//sort events related to a client based on its time using insertionsort
//guarantes query answer in chronological order 
void  QueriesExecutor::sortEvents(Event* events, int numEvents){
    int j;
    for (int i = 0 + 1; i < numEvents; i++)
    {
        Event round_item = events[i];
        j = i - 1;

        while (j >= 0 && round_item.key < events[j].key)
        {
        events[j + 1] = events[j];
        j--;
        }
        events[j + 1] = round_item;
    }
    return;
}

//executes client query 
void QueriesExecutor::executeClientQuery(Query clientQuery, EventStorage& events, ClientsStorage& clients, PackageStorage& packages){
    //gets all packages related to client
    List<int> clientPackages = clients.getPackages(clientQuery.client);
    int numPackages = clientPackages.getSize();

    //create and populate array containing first and last event of each package 
    Event* clientPackagesEvents = new Event[numPackages * 2];
    for(int i =0;i<numPackages;++i){
        int packageId = clientPackages.getItem(i+1);
        int firstEvent = 0, lastEvent = 0;
        packages.getFirstAndLastPakageEvent(packageId, &firstEvent, &lastEvent);
        clientPackagesEvents[2*i] = events.getEvent(firstEvent);
        clientPackagesEvents[2*i+1] = events.getEvent(lastEvent);
    } 
    //guarantees that events are in chronological order 
    this->sortEvents(clientPackagesEvents, numPackages * 2);
    //prints answer
    std::cout<< std::setfill('0') << std::setw(6) << clientQuery.time<<" CL "<<clientQuery.client<<std::endl;
    std::cout<<numPackages * 2<<std::endl;
    for(int i =0;i<numPackages * 2;i++){
        events.printEvent(clientPackagesEvents[i]);
    }
    delete[] clientPackagesEvents;
}

//executes packages queries
void QueriesExecutor::executePackageQuery(Query packageQuery, EventStorage& events,  PackageStorage& packages){
    //get list of events of a package
    List<PackageEvent> packageEvents = packages.getPackagesEvent(packageQuery.package_id);
    int numEvents = packageEvents.getSize();
    //prints all events
    std::cout<< std::setfill('0') << std::setw(6) << packageQuery.time<<" PC "<<std::setfill('0') << std::setw(3)<<packageQuery.package_id<<std::endl;
    std::cout<<numEvents<<std::endl;
    for(int i =0;i<numEvents;++i){
        //gets all information of an event at EventStorage
        PackageEvent currentPackageEvent = packageEvents.getItem(i+1);
        int eventId = currentPackageEvent.eventId;
        Event currentEvent = events.getEvent(eventId);
        events.printEvent(currentEvent);
    }
}

void QueriesExecutor::executeAllQueries(EventStorage& events, ClientsStorage& clients, PackageStorage& packages){
    int  start = 0 ;
    //executes all queries stored
    for(int j=0;j<this->numQueries;++j){
        //update end so we only consider events ocurred before query 
        int end = this->queries[j].last_event_until_querie;
        for(int i = start; i<=end;++i){
            Event current_event = events.getEvent(i);
            if(current_event.eventType == "RG"){
                //add clients if they aren't registered yet
                if(!clients.isClientRegistered(current_event.sender)){
                    clients.addClient(current_event.sender);
                }
                if(!clients.isClientRegistered(current_event.recipient)){
                    clients.addClient(current_event.recipient);
                }
                clients.addPackageToClients(current_event.sender, current_event.recipient, current_event.packageId);
                //add packages
                packages.addPackage(current_event.packageId, i, current_event.time);
            }else{
                //add last event to a package
                packages.addEventToPackage(current_event.packageId, i, current_event.time);
            }
        }
        //checks query type and executes it 
        if (this->queries[j].type == "PC") {
            this->executePackageQuery(this->queries[j], events, packages);
        }else if(this->queries[j].type == "CL") {
            this->executeClientQuery(this->queries[j], events, clients, packages);
        }else if(this->queries[j].type == "CTA"){
            this->executeWarehouseQueriesAtTimeInterval(this->queries[j],  events);
        }else if(this->queries[j].type == "CTP"){
            this->executePackageQueriesAtTimeInterval(this->queries[j],  events);
        }
        start = end +1;
    }
}

void QueriesExecutor::executeWarehouseQueriesAtTimeInterval(Query query, EventStorage& events){
    int left = -1, right = events.getCurrentSize();
    while(left < right - 1){
        int middle = (left + right)/2;
        if(events.getEvent(middle).time < query.initialTime){
            left = middle;
        }else{
            right = middle;
        }
    }
    int i = right; 
 
    std::cout<< std::setfill('0') << std::setw(6) << query.time<<" CTA "
    <<std::setfill('0') << std::setw(3) <<query.warehouseId<<" "<<
    std::setfill('0') << std::setw(3) <<query.initialTime<<" "<<
    std::setfill('0') << std::setw(3) <<query.finalTime<<std::endl;
    while( i < events.getCurrentSize() && events.getEvent(i).time <= query.finalTime){
        Event e = events.getEvent(i);
        if(e.warehouseDestination == query.warehouseId || e.warehouseOrigin == query.warehouseId){
            events.printEvent(e);
        }
        i++;
    }
}

void QueriesExecutor::executePackageQueriesAtTimeInterval(Query query, EventStorage& events){
    int left = -1, right = events.getCurrentSize();
    while(left < right - 1){
        int middle = (left + right)/2;
        if(events.getEvent(middle).time < query.initialTime){
            left = middle;
        }else{
            right = middle;
        }
    }
    int i = right; 
 
    std::cout<< std::setfill('0') << std::setw(6) << query.time<<" CTP "
    <<std::setfill('0') << std::setw(3) <<query.package_id<<" "<<
    std::setfill('0') << std::setw(3) <<query.initialTime<<" "<<
    std::setfill('0') << std::setw(3) <<query.finalTime<<std::endl;
    while( i < events.getCurrentSize() && events.getEvent(i).time <= query.finalTime){
        Event e = events.getEvent(i);
        if(e.packageId == query.package_id){
            events.printEvent(e);
        }
        i++;
    }
}