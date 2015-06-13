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
    void save(entryRow_t entryRow);
    void update(entryRow_t entryRow);
    void retrieve(char nombre[61]);
    void deleteEntry(char nombre[61]);
};

#endif //CONCU_LUCAS_FEDE_TP2_DATABASEMANAGER_H
