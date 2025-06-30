#ifndef QUERIESEXECUTOR_HPP
#define QUERIESEXECUTOR_HPP
#include <string>
#include "ClientsStorage.hpp"
#include "EventStorage.hpp"
#include "PackageStorage.hpp"
struct Query{
    int time = 0;
    int package_id = -1;
    std::string client = "";
    int last_event_until_querie;
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
    void sortEvents(Event* events, int numEvents);
};

#endif