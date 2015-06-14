//
// Created by fede on 13/06/15.
//

#include "Client.h"

Client::Client() : Process() {
    if (clientIdShMem.crear(SHARED_MEM_CLIENT_ID, 'L') != SHM_OK){
        string error = "Error creating Client Id Shared Mem";
        perror(error.c_str());
        Logger::logger().log(error);
    }

    clientIdLock.tomarLockWr();
    clientId = clientIdShMem.leer();
    clientIdShMem.escribir(clientId + 1);
    clientIdLock.liberarLock();

    Logger::logger().log("Client " + to_string(clientId) + " Initialized");
}

void Client::start() {
    Logger::logger().log("Client " + to_string(clientId) + " Running");

    string nombre1 = "Foo";
    string direccion1 = "Avenida del Foo";
    string telefono1 = "3-14159-2653";

    string nombre2 = "Bar";
    string direccion2 = "Avenida del Bar";
    string telefono2 = "2-7182-8182";

    entryRow_t entryRow;
    strcpy(entryRow.nombre, nombre1.c_str());
    strcpy(entryRow.direccion, direccion1.c_str());
    strcpy(entryRow.telefono, telefono1.c_str());

    save(entryRow);

    // GracefulQuit
    Logger::logger().log("Client " + to_string(clientId) + " Quit");
}

int Client::save(entryRow_t entryRow) {
    Logger::logger().log("Client " + to_string(clientId) + " Saving");

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    dbQuery.entryRow = entryRow;
    dbQuery.action = SAVE;

    int result = msgQueueQueries.escribir(dbQuery);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Saving/Query");
        return -1;
    }

    dbResponse_t dbResponse;
    result = msgQueueResponses.leer(clientId, &dbResponse);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Saving/Response");
        return -1;
    }

    if (dbResponse.result < 0)
        Logger::logger().log("Client " + to_string(clientId) + " Error Saving/DB");
    else
        Logger::logger().log("Client " + to_string(clientId) + " Saving Successful");

    return 0;
}

int Client::update(entryRow_t entryRow) {
    Logger::logger().log("Client " + to_string(clientId) + " Updating");
    return 0;
}

entryRow_t Client::retrieve(char nombre[61]) {
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving");

    entryRow_t entryRow;

    return entryRow;
}

int Client::deleteEntry(char nombre[61]) {
    Logger::logger().log("Client " + to_string(clientId) + " Deleting");
    return 0;
}