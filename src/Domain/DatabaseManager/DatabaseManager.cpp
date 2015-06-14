//
// Created by fede on 13/06/15.
//

#include <fstream>
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
    }

    // GracefulQuit
    Logger::logger().log("DatabaseManager Quit");
    msgQueueQueries.destruir();
    msgQueueResponses.destruir();
    clientIdShMem.liberar();
}

void padTo(std::string &str, const size_t num, const char paddingChar = ' ')
{
    if(num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}

int DatabaseManager::save(dbQuery_t dbQuery) {
    Logger::logger().log("DatabaseManager Saving for client " + to_string(dbQuery.mtype));

    string nombre = string(dbQuery.entryRow.nombre);
    string direccion = string(dbQuery.entryRow.direccion);
    string telefono = string(dbQuery.entryRow.telefono);
    padTo(nombre, NOMBRE_SIZE - 1);
    padTo(direccion, DIRECCION_SIZE - 1);
    padTo(telefono, TELEFONO_SIZE - 1);
    string entryRowLine = nombre + direccion + telefono;
    cout << entryRowLine << endl;

    ofstream persistenceFile;
    persistenceFile.open(PERSISTENCE_FILE, fstream::app);
    persistenceFile << entryRowLine << endl;
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