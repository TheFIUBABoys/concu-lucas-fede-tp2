//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
#define CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H

#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"
#include "../../Util/MemoriaCompartida/MemoriaCompartida.h"

class DatabaseManager : Process {
public:
    DatabaseManager();
    void start();
private:
    Cola<dbQuery_t> msgQueueQueries = Cola<dbQuery_t>(MSG_QUEUE_QUERIES_NAME, 'a' );
    Cola<dbResponse_t> msgQueueResponses = Cola<dbResponse_t>(MSG_QUEUE_RESPONSES_NAME, 'a' );
    MemoriaCompartida<int> clientIdShMem;
    int save(dbQuery_t dbQuery);
    int update(dbQuery_t dbQuery);
    int retrieve(dbQuery_t dbQuery);
    int deleteEntry(dbQuery_t dbQuery);
};

#endif //CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
