#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "EventStorage.hpp"
#include "QueriesExecutor.hpp"



int main(int argc, char*argv[]) {

    std::string file_name, line;
    
    //opening file
    if (argc != 2) {
        std::cerr << "Erro: file name needed" << std::endl;
        return 1;
    }
    
    file_name = argv[1];
    
    std::ifstream file(file_name);
    
    if (!file) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    EventStorage events;
    ClientsStorage clients;
    QueriesExecutor querieExecutor;
    PackageStorage packages;
    auto start1 = std::chrono::high_resolution_clock::now();
    //reading file 
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        int time;
        iss >> time;
        //file ended
        if (!iss) break; 

        std::string event_code;
        iss >> event_code;
        //reads and store events based on their types
        if(event_code == "EV"){
            std::string event_type;
            iss >> event_type;
            if(event_type == "RG"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.sender;
                iss >> new_event.recipient;
                iss >> new_event.warehouseOrigin;
                iss >> new_event.warehouseDestination;
                iss >> new_event.destinationSection;
                events.addEvent(new_event);


            }else if(event_type == "AR"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.warehouseDestination;
                iss >> new_event.destinationSection;
                events.addEvent(new_event);
            }else if(event_type == "RM"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.warehouseDestination;
                iss >> new_event.destinationSection;
                events.addEvent(new_event);

            }else if(event_type == "UR"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.warehouseDestination;
                iss >> new_event.destinationSection;
                events.addEvent(new_event);
            
            }else if(event_type == "TR"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.warehouseOrigin;
                iss >> new_event.warehouseDestination;
                events.addEvent(new_event);

            }else if(event_type == "EN"){
                Event new_event;
                new_event.time = time;
                new_event.eventType = event_type;
                iss >> new_event.packageId;
                iss >> new_event.warehouseDestination;
                events.addEvent(new_event);

            }else{
                std::cerr<<"Error: evento invalido\n";
            }
            //store packages queries
        }else if(event_code == "PC"){
            Query newQuery;
            newQuery.time = time;
            iss >> newQuery.package_id;
            newQuery.last_event_until_querie = events.getCurrentSize() -1 ;
            querieExecutor.addQuerie(newQuery);
            //store clients queries 
        }else if(event_code == "CL"){
            Query newQuery;
            newQuery.time = time;
            iss >> newQuery.client;
            newQuery.last_event_until_querie = events.getCurrentSize()-1;
            querieExecutor.addQuerie(newQuery);
        }else{
            std::cerr<<"Error: acao invalida\n";
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration1 = end1 - start1;
    //executes all queries 
    auto start = std::chrono::high_resolution_clock::now();
    querieExecutor.executeAllQueries(events, clients, packages);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::micro> duration = end - start;
    std::cout<<"Duracao Leitura: "<<duration1.count()<<std::endl;
    std::cout<<"Duracao: "<<duration.count()<<std::endl;
    
    return 0;
}
