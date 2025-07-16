#ifndef CLIENTSTORAGE_HPP
#define CLIENTSTORAGE_HPP
#include <string>
#include "List.hpp"
#include "AVLTree.hpp"
struct Client{
    std::string name;
    List<int> relatedPackages;

    friend bool operator<(const Client& a, const Client& b) {
        return a.name < b.name;
    }
    friend bool operator>(const Client& a, const Client& b) {
        return a.name > b.name;
    }
    friend bool operator==(const Client& a, const Client& b) {
        return a.name == b.name;
    }
    friend std::ostream& operator<<(std::ostream& os, Client const& c) {
        return os << c.name;
    }
};

class ClientsStorage{
    private:
    AVLTree<Client> clientsIndex;
    public:
    void addClient(std::string name);
    void addPackageToClients(std::string sender, std::string, int packageId);
    bool isClientRegistered(std::string name);
    List<int> getPackages(std::string clientName);
};

#endif