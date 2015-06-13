//
// Created by fede on 13/06/15.
//

#include "Client.h"

Client::Client() : Process() {
    Logger::logger().log("Client Initialized");
}

void Client::start() {
    Logger::logger().log("Client Running");

    const std::string ARCHIVO = MSG_QUEUE_NAME;
    Cola<dbAction_t> msgQueue ( ARCHIVO, 1 );

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
    Logger::logger().log("Client Quit");
    msgQueue.destruir();
}

int Client::save(entryRow_t entryRow) {
    Logger::logger().log("Client Saving");

    dbAction_t dbAction;
    dbAction.mtype = DB_QUERY;
    dbAction.entryRow = entryRow;
    dbAction.action = SAVE;

    return 0;
}

int Client::update(entryRow_t entryRow) {
    Logger::logger().log("Client Updating");
    return 0;
}

entryRow_t Client::retrieve(char nombre[61]) {
    Logger::logger().log("Client Retrieving");

    entryRow_t entryRow;

    return entryRow;
}

int Client::deleteEntry(char nombre[61]) {
    Logger::logger().log("Client Deleting");
    return 0;
}