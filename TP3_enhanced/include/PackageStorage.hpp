#ifndef PACKAGESTORAGE_HPP
#define PACKAGESTORAGE_HPP
#include <iostream>
#include "AVLTree.hpp"
#include "List.hpp"
#include "Queue.hpp"
#include "EventStorage.hpp"
struct PackageEvent{
    int time = 0;
    int eventId = -1;

    friend bool operator<(const PackageEvent& a, const PackageEvent& b) {
        return a.time < b.time;
    }
    friend bool operator>(const PackageEvent& a, const PackageEvent& b) {
        return a.time > b.time;
    }
    friend bool operator==(const PackageEvent& a, const PackageEvent& b) {
        return a.time == b.time;
    }
    friend std::ostream& operator<<(std::ostream& os, PackageEvent const& c) {
        return os << c.time;
    }
};

struct Package{
    int packageId = -1;
    int startEventId = -1;
    int endEventId = -1;
    List<PackageEvent> packagesEvent;
    friend bool operator<(const Package& a, const Package& b) {
        return a.packageId < b.packageId;
    }
    friend bool operator>(const Package& a, const Package& b) {
        return a.packageId > b.packageId;
    }
    friend bool operator==(const Package& a, const Package& b) {
        return a.packageId == b.packageId;
    }
    friend std::ostream& operator<<(std::ostream& os, Package const& c) {
        return os << c.packageId<< " "<<c.startEventId<<" "<<c.endEventId<<"\n";
    }
};

class PackageStorage{
    private:
    AVLTree<Package> packages;
    public:
    void addPackage(int packageId, int startEventId, int time);
    void addEventToPackage(int packageId, int eventId, int time);
    void alterLastPackageEvent(int newEventId, int packageId);
    void addStartEvent(int firstEventId, int packageId);
    List<PackageEvent> getPackagesEvent(int packageId);
    void getFirstAndLastPakageEvent(int packageId, int* firstEventId, int* lastEventId);
};

#endif