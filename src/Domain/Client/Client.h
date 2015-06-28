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
#include "../../Util/Seniales/SIGINT_Handler.h"
#include "../../Util/Seniales/SignalHandler.h"

typedef enum ClientResponse{
    ClientResponseOK,
    ClientResponseError,
    ClientResponseRepeated

} ClientResponse;
class Client {
public:
    Client();
    ClientResponse save(Persona& persona);
    Persona getByName(string name);

private:
    Cola<dbQuery_t> msgQueueQueries;
    Cola<dbResponse_t> msgQueueResponses;
    int clientId;
    bool checkDBManager();
    int handleSignal(int signum);
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
