//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_CLIENT_H
#define CONCU_LUCAS_FEDE_TP2_CLIENT_H

#include <stdio.h>
#include <string>
#include <string.h>
#include "../../Exception/InvalidParamsException.h"
#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"
#include "../Persona/Persona.h"

typedef enum ClientResponse{
    ClientResponseOK,
    ClientResponseError,
    ClientResponseRepeated

} ClientResponse;
class Client : Process {
public:
    Client();
    ClientResponse save(Persona& persona);
    Persona getByName(string name);

private:
    Cola<dbQuery_t> msgQueueQueries;
    Cola<dbResponse_t> msgQueueResponses;
    int clientId;
    bool checkDBManager();
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
