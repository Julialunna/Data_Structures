#ifndef QUERIESEXECUTOR_HPP
#define QUERIESEXECUTOR_HPP
#include <string>
#include "ClientsStorage.hpp"
#include "EventStorage.hpp"
#include "PackageStorage.hpp"
struct Query{
    std::string type;
    int time = 0;
    int package_id = -1;
    std::string client = "";
    int last_event_until_querie;
    int initialTime = -1;
    int finalTime = -1;
    int warehouseId = 0;
};

class QueriesExecutor{
    private:
    Query* queries;
    int numQueries;
    int maxNumQueries;
    public:
    void addQuerie(Query new_query);
    QueriesExecutor();
    ~QueriesExecutor();
    void increaseSize();
    void executeClientQuery(Query clientQuery, EventStorage& events, ClientsStorage& clients, PackageStorage& packages);
    void executePackageQuery(Query packageQuery, EventStorage& events,  PackageStorage& packages);
    void executeAllQueries(EventStorage& events, ClientsStorage& clients, PackageStorage& packages);
    void executeWarehouseQueriesAtTimeInterval(Query query, EventStorage& events);
    void executePackageQueriesAtTimeInterval(Query query, EventStorage& events);
    void sortEvents(Event* events, int numEvents);
};

#endif