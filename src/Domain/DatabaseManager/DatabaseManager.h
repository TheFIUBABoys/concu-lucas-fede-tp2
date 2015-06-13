//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
#define CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H

#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"

class DatabaseManager : Process {
public:
    DatabaseManager();
    void start();
private:
    int save(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery);
    int update(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery);
    int retrieve(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery);
    int deleteEntry(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery);
};

#endif //CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
