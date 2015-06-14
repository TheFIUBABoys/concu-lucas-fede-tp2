//
// Created by fede on 13/06/15.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : Process() {
    Logger::logger().log("DatabaseManager Initialized");

    if (clientIdShMem.crear(SHARED_MEM_CLIENT_ID, 'L') != SHM_OK){
        string error = "Error creating Client Id Shared Mem";
        perror(error.c_str());
        Logger::logger().log(error);
    }

    clientIdShMem.escribir(1);
}

void DatabaseManager::start() {
    Logger::logger().log("DatabaseManager Running");

    dbQuery_t dbQuery;
    msgQueueQueries.leer(0, &dbQuery);

    switch (dbQuery.action){
        case SAVE:
            save(dbQuery);
            break;
        case UPDATE:
            update(dbQuery);
            break;
        case RETRIEVE:
            retrieve(dbQuery);
            break;
        case DELETE:
            deleteEntry(dbQuery);
            break;
    }

    sleep(5);

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueueQueries.destruir();
    msgQueueResponses.destruir();
    clientIdShMem.liberar();
}

int DatabaseManager::save(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Saving for client " + to_string(dbQuery.mtype));

    // TODO: Inicializar persona en base a entry row; guardar en archivo

    dbResponse_t dbResponse;
    dbResponse.mtype = dbQuery.mtype;
    dbResponse.result = 0;

    int result = msgQueueResponses.escribir(dbResponse);
    if (result < 0) {
        Logger::logger().log("DatabaseManager Response Error");
        return -1;
    }

    return 0;
}

int DatabaseManager::update(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Updating for client " + to_string(dbQuery.mtype));

    return 0;
}

int DatabaseManager::retrieve(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Retrieving for client " + to_string(dbQuery.mtype));

    return 0;
}

int DatabaseManager::deleteEntry(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Deleting for client " + to_string(dbQuery.mtype));

    return 0;
}