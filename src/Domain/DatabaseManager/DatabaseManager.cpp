//
// Created by fede on 13/06/15.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : Process() {
    Logger::logger().log("DatabaseManager Initialized");
}

void DatabaseManager::start() {
    Logger::logger().log("DatabaseManager Running");

    const std::string ARCHIVO = MSG_QUEUE_NAME;
    Cola<dbAction_t> msgQueue ( ARCHIVO, 1 );

    dbAction_t dbAction;
    msgQueue.leer(0, &dbAction);

    switch (dbAction.action){
        case SAVE:
            save(dbAction.entryRow);
            break;
        case UPDATE:
            update(dbAction.entryRow);
            break;
        case RETRIEVE:
            retrieve(dbAction.nombre);
            break;
        case DELETE:
            deleteEntry(dbAction.nombre);
            break;
    }

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueue.destruir();
}

void DatabaseManager::save(entryRow_t entryRow) {
    Logger::logger().log("DatabaseManager Saving");
}

void DatabaseManager::update(entryRow_t entryRow) {
    Logger::logger().log("DatabaseManager Updating");
}

void DatabaseManager::retrieve(char nombre[61]) {
    Logger::logger().log("DatabaseManager Retrieving");
}

void DatabaseManager::deleteEntry(char nombre[61]) {
    Logger::logger().log("DatabaseManager Deleting");
}