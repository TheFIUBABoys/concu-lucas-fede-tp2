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
    MemoriaCompartida<int> clientIdShMem;
    LockFile clientIdLock = LockFile(SHARED_MEM_CLIENT_ID);
    int clientId;
    int save(Cola<dbQuery_t> msgQueueQueries, Cola<dbResponse_t> msgQueueResponses, entryRow_t entryRow);
    int update(Cola<dbQuery_t> msgQueue, Cola<dbResponse_t> msgQueueResponses, entryRow_t entryRow);
    entryRow_t retrieve(Cola<dbQuery_t> msgQueue, Cola<dbResponse_t> msgQueueResponses, char nombre[61]);
    int deleteEntry(Cola<dbQuery_t> msgQueue, Cola<dbResponse_t> msgQueueResponses, char nombre[61]);
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
