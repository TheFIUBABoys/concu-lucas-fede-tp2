//
// Created by fede on 13/06/15.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : Process() {
    Logger::logger().log("DatabaseManager Initialized with pid " + to_string(getpid()));

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
    while(!sigint_handler.getGracefulQuit()) {
        int resultado = msgQueueQueries.leer(0, &dbQuery);
        if (resultado < 0)
            break;

        switch (dbQuery.action){
            case SAVE:
                save(dbQuery);
                break;
            case RETRIEVE:
                retrieve(dbQuery);
                break;
        }
    }

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueueQueries.destruir();
    msgQueueResponses.destruir();
    clientIdShMem.liberar();

    deleteTempfiles();
}

void DatabaseManager::deleteTempfiles() {//Creating temp lock files
    remove(MSG_QUEUE_QUERIES_NAME);
    remove(MSG_QUEUE_RESPONSES_NAME);
    remove(SHARED_MEM_CLIENT_ID);
}

int DatabaseManager::save(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Saving for client " + to_string(dbQuery.mtype));

    entryRow_t entryRow = dbQuery.entryRow;
    Persona persona = Persona(entryRow.nombre, entryRow.direccion, entryRow.telefono);

    ofstream persistenceFile;
    persistenceFile.open(PERSISTENCE_FILE, fstream::app);
    persistenceFile << persona.getStringRepresentation() << endl;
    persistenceFile.close();

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

int DatabaseManager::retrieve(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Retrieving for client " + to_string(dbQuery.mtype));

    dbResponse_t dbResponse;
    dbResponse.mtype = dbQuery.mtype;
    dbResponse.result = -1;

    string line;
    string nombreRetrieve = string(dbQuery.nombre);
    MixedUtils::padTo(nombreRetrieve, NOMBRE_SIZE - 1);
    ifstream persistenceFile(PERSISTENCE_FILE);
    if (persistenceFile.is_open()) {
        while (getline(persistenceFile, line)) {
            if (line.compare(0, NOMBRE_SIZE - 1, nombreRetrieve) == 0) {
                strcpy(dbResponse.value, line.c_str());
                dbResponse.result = 0;
                break;
            }
        }
        persistenceFile.close();
    }

    int result = msgQueueResponses.escribir(dbResponse);
    if (result < 0) {
        Logger::logger().log("DatabaseManager Response Error");
        return -1;
    }

    return 0;
}