//
// Created by fede on 13/06/15.
//

#include "Client.h"

Client::Client() : Process() {
    clientId = 1;

    Logger::logger().log("Client " + to_string(clientId) + " Initialized");
}

void Client::start() {
    Logger::logger().log("Client Running");

    const std::string QUERIES_FILE = MSG_QUEUE_QUERIES_NAME;
    Cola<dbQuery_t> msgQueueQueries(QUERIES_FILE, 'a' );

    const std::string RESPONSES_FILE = MSG_QUEUE_RESPONSES_NAME;
    Cola<dbResponse_t> msgQueueResponses(RESPONSES_FILE, 'a' );

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

    save(msgQueueQueries, msgQueueResponses, entryRow);

    // GracefulQuit
    Logger::logger().log("Client Quit");
}

int Client::save(Cola<dbQuery_t> msgQueueQueries, Cola<dbResponse_t> msgQueueResponses, entryRow_t entryRow) {
    Logger::logger().log("Client " + to_string(clientId) + " Saving");

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    dbQuery.entryRow = entryRow;
    dbQuery.action = SAVE;

    int result = msgQueueQueries.escribir(dbQuery);
    if (result < 0) {
        Logger::logger().log("Client Error Saving/Query");
        return -1;
    }

    dbResponse_t dbResponse;
    result = msgQueueResponses.leer(clientId, &dbResponse);
    if (result < 0) {
        Logger::logger().log("Client Error Saving/Response");
        return -1;
    }

    if (dbResponse.result < 0)
        Logger::logger().log("Client Error Saving/DB");
    else
        Logger::logger().log("Client Saving Successful");

    return 0;
}

int Client::update(Cola<dbQuery_t> msgQueueQueries, Cola<dbResponse_t> msgQueueResponses, entryRow_t entryRow) {
    Logger::logger().log("Client " + to_string(clientId) + " Updating");
    return 0;
}

entryRow_t Client::retrieve(Cola<dbQuery_t> msgQueueQueries, Cola<dbResponse_t> msgQueueResponses, char nombre[61]) {
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving");

    entryRow_t entryRow;

    return entryRow;
}

int Client::deleteEntry(Cola<dbQuery_t> msgQueueQueries, Cola<dbResponse_t> msgQueueResponses, char nombre[61]) {
    Logger::logger().log("Client " + to_string(clientId) + " Deleting");
    return 0;
}