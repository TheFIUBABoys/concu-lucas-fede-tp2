//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_CLIENT_H
#define CONCU_LUCAS_FEDE_TP2_CLIENT_H

#include <string.h>
#include "../../Domain/EntryRow/entryRow.h"
#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Cola/Cola.h"

class Client : Process {
public:
    Client();
    void start();
private:
    int save(entryRow_t entryRow);
    int update(entryRow_t entryRow);
    entryRow_t retrieve(char nombre[61]);
    int deleteEntry(char nombre[61]);
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
