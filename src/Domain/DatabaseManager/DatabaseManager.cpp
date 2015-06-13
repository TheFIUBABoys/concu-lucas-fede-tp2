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

    const std::string QUERIES_FILE = MSG_QUEUE_QUERIES_NAME;
    Cola<dbQuery_t> msgQueueQueries(QUERIES_FILE, 'a' );

    const std::string RESPONSES_FILE = MSG_QUEUE_RESPONSES_NAME;
    Cola<dbResponse_t> msgQueueResponses(RESPONSES_FILE, 'a' );

    dbQuery_t dbQuery;
    msgQueueQueries.leer(0, &dbQuery);

    switch (dbQuery.action){
        case SAVE:
            save(msgQueueResponses, dbQuery);
            break;
        case UPDATE:
            update(msgQueueResponses, dbQuery);
            break;
        case RETRIEVE:
            retrieve(msgQueueResponses, dbQuery);
            break;
        case DELETE:
            deleteEntry(msgQueueResponses, dbQuery);
            break;
    }

    sleep(5);

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueueQueries.destruir();
    msgQueueResponses.destruir();
    clientIdShMem.liberar();
}

int DatabaseManager::save(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Saving for client " + to_string(dbQuery.mtype));

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

int DatabaseManager::update(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Updating for client " + to_string(dbQuery.mtype));

    return 0;
}

int DatabaseManager::retrieve(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Retrieving for client " + to_string(dbQuery.mtype));

    return 0;
}

int DatabaseManager::deleteEntry(Cola<dbResponse_t> msgQueueResponses, dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Deleting for client " + to_string(dbQuery.mtype));

    return 0;
}