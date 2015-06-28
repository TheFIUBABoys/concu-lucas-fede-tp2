//
// Created by fede on 13/06/15.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : Process() {
    try {
        msgQueueQueries = Cola<dbQuery_t>(MSG_QUEUE_QUERIES_NAME, 'a');
        msgQueueResponses = Cola<dbResponse_t>(MSG_QUEUE_RESPONSES_NAME, 'a');
        Logger::logger().log("DatabaseManager Initialized with pid " + to_string(getpid()));
    }catch (MessageQueueException e){
        Logger::logger().log("Error initializing manager:  " + string(e.what()));
    }
}

void DatabaseManager::start() {
    Logger::logger().log("DatabaseManager Running");

    dbQuery_t dbQuery;
    while(!sigint_handler.getGracefulQuit()) {
        int resultado = msgQueueQueries.leer(0, &dbQuery);
        if (resultado < 0){
            Logger::logger().log("DatabaseManager read EOF");
            break;
        }
        switch (dbQuery.action){
            case SAVE:
                save(dbQuery);
                break;
            case RETRIEVE:
                retrieveByName(dbQuery);
                break;
            default:
                break;
        }
    }

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueueQueries.destruir();
    msgQueueResponses.destruir();
    deleteTempfiles();
}

void DatabaseManager::deleteTempfiles() {//Creating temp lock files
    remove(MSG_QUEUE_QUERIES_NAME);
    remove(MSG_QUEUE_RESPONSES_NAME);
}

int DatabaseManager::save(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager saving for client " + to_string(dbQuery.mtype));
    dbQuery_t testQuery = dbQuery;
    testQuery.action = RETRIEVE;
    strcpy(testQuery.nombre, dbQuery.entryRow.nombre);
    dbResponse_t retrieveResult = retrieveQuery(testQuery);
    if (retrieveResult.result == ResponseTypeAlreadyExists){
        //Entry already exists
        Logger::logger().log("DatabaseManager attempted to insert repeated entry");
        dbResponse_t dbResponse;
        dbResponse.mtype = dbQuery.mtype;
        strcpy(dbResponse.value, retrieveResult.value);
        dbResponse.result = ResponseTypeAlreadyExists;
        int result = msgQueueResponses.escribir(dbResponse);
        if (result < 0) {
            Logger::logger().log("DatabaseManager: Error writing response");
        }
        return -1;
    }

    entryRow_t entryRow = dbQuery.entryRow;
    Persona persona = Persona(entryRow.nombre, entryRow.direccion, entryRow.telefono);

    ofstream persistenceFile;
    persistenceFile.open(PERSISTENCE_FILE, fstream::app);
    persistenceFile << persona.getStringRepresentation() << endl;
    persistenceFile.close();

    dbResponse_t dbResponse;
    dbResponse.mtype = dbQuery.mtype;
    dbResponse.result = ResponseTypeOK;

    int result = msgQueueResponses.escribir(dbResponse);
    if (result < 0) {
        Logger::logger().log("DatabaseManager: Error writing response");
        return -1;
    }

    return 0;
}

int DatabaseManager::retrieveByName(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Retrieving for client " + to_string(dbQuery.mtype));
    dbResponse_t dbResponse = retrieveQuery(dbQuery);

    int result = msgQueueResponses.escribir(dbResponse);
    if (result < 0) {
        Logger::logger().log("DatabaseManager Response Error");
        return -1;
    }

    return 0;
}

dbResponse_t DatabaseManager::retrieveQuery(dbQuery_t &dbQuery) {
    dbResponse_t dbResponse;
    dbResponse.mtype = dbQuery.mtype;
    dbResponse.result = ResponseTypeOK;
    string line;
    string nombreRetrieve = string(dbQuery.nombre);
    MixedUtils::padTo(nombreRetrieve, NOMBRE_SIZE - 1);
    ifstream persistenceFile(PERSISTENCE_FILE);
    if (persistenceFile.is_open()) {
        while (getline(persistenceFile, line)) {
            if (line.compare(0, NOMBRE_SIZE - 1, nombreRetrieve) == 0) {
                strcpy(dbResponse.value, line.c_str());
                dbResponse.result = ResponseTypeAlreadyExists;
                break;
            }
        }
        persistenceFile.close();
    }
    return dbResponse;
}