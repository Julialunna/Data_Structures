#include "PackageStorage.hpp"
//Alter on package resgister its last event using its index on event storage
void PackageStorage::alterLastPackageEvent(int newEventId, int packageId){
    Package* packageToAlter = this->packages.find(packageId);
    if(!packageToAlter){
        std::cerr<<"Error: pacote nao encontrado\n";
    }else{
        packageToAlter->endEventId = newEventId; 
    }
}
//Adds first event at package register using its index on event storage
void PackageStorage::addStartEvent(int firstEventId, int packageId){
    Package* packageToAlter = this->packages.find(packageId);
    if(!packageToAlter){
        std::cerr<<"Error: pacote nao encontrado\n";
    }else{
        packageToAlter->endEventId = firstEventId;
    }
}
//gets list of events related to a package using its id
List<PackageEvent> PackageStorage::getPackagesEvent(int packageId){
    Package* package = this->packages.find(packageId);
    if(!package){
        std::cerr<<"Error: pacote nao encontrado\n";
    }else{
        return package->packagesEvent;
    }
    return List<PackageEvent>();
}
//gets first and last events index related to a package 
//function used to clients queries
void PackageStorage::getFirstAndLastPakageEvent(int packageId, int* firstEventId, int* lastEventId){
    Package* packageToQuery = this->packages.find(packageId);
    if(!packageToQuery){
        std::cerr<<"Error: pacote nao encontrado\n";
    }else{
        *(firstEventId) = packageToQuery->startEventId;
        *(lastEventId) = packageToQuery->endEventId;
    }
}
//adds package on packagesAVLTree and defines its first event
void PackageStorage::addPackage(int packageId, int startEventId, int time){
    Package newPackage;
    newPackage.packageId = packageId;
    newPackage.startEventId = startEventId;
    newPackage.endEventId = startEventId;
    this->packages.insert(newPackage);
    this->addEventToPackage(packageId, startEventId, time);

}
//adds event at events list of a package
void PackageStorage::addEventToPackage(int packageId, int eventId, int time){
    Package* packageToAlter = this->packages.find(packageId);
    if(!packageToAlter){
        std::cerr<<"Error: pacote nao encontrado\n";
    }else{
        PackageEvent newEvent;
        newEvent.eventId = eventId;
        newEvent.time = time;
        packageToAlter->packagesEvent.insertEnd(newEvent);
        packageToAlter->endEventId = eventId;
    }
}

