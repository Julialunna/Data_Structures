#include "ClientsStorage.hpp"

//insert client at clients AVLTree
void ClientsStorage::addClient(std::string name){
    Client newCliente;
    newCliente.name = name;
    this->clientsIndex.insert(newCliente);
    
}

//adds packages id to both sender and recipient clients 
void ClientsStorage::addPackageToClients(std::string sender, std::string recipient, int PackageId){
    Client* recipientClient = this->clientsIndex.find(recipient);
    if(recipientClient != nullptr){
        recipientClient->relatedPackages.insertEnd(PackageId);
    }
    Client* senderClient = this->clientsIndex.find(sender);
    if(senderClient != nullptr){
        senderClient->relatedPackages.insertEnd(PackageId);
    }
}

//checks if client register is at AVLTree
bool ClientsStorage::isClientRegistered(std::string name){
    if(!this->clientsIndex.find(name)){
        return false;
    }else{
        return true;
    }
}


//gets packages id that are related to the client 
List<int> ClientsStorage::getPackages(std::string clientName){
    Client* client = this->clientsIndex.find(clientName);
    if(client != nullptr){
        return client->relatedPackages;
    }
    return List<int>();
}