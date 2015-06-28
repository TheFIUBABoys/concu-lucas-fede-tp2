//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
#define CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H

#include <fstream>
#include <string.h>
#include "../Persona/Persona.h"
#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"
#include "../../Util/MixedUtils.h"

class DatabaseManager : Process {
public:
    DatabaseManager();
    void start();
private:
    Cola<dbQuery_t> msgQueueQueries;
    Cola<dbResponse_t> msgQueueResponses;
    int save(dbQuery_t dbQuery);
    int retrieve(dbQuery_t dbQuery);

    void deleteTempfiles();
};

#endif //CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
