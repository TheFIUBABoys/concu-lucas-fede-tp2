//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_CLIENT_H
#define CONCU_LUCAS_FEDE_TP2_CLIENT_H

#include <stdio.h>
#include <string.h>
#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"
#include "../../Util/MemoriaCompartida/MemoriaCompartida.h"

class Client : Process {
public:
    Client();
    void start();
private:
    Cola<dbQuery_t> msgQueueQueries = Cola<dbQuery_t>(MSG_QUEUE_QUERIES_NAME, 'a' );
    Cola<dbResponse_t> msgQueueResponses = Cola<dbResponse_t>(MSG_QUEUE_RESPONSES_NAME, 'a' );
    MemoriaCompartida<int> clientIdShMem;
    LockFile clientIdLock = LockFile(SHARED_MEM_CLIENT_ID);
    int clientId;
    int save(entryRow_t entryRow);
    int update(entryRow_t entryRow);
    entryRow_t retrieve(char nombre[61]);
    int deleteEntry(char nombre[61]);
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
