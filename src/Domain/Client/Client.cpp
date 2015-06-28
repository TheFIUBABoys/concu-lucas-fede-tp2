//
// Created by fede on 13/06/15.
//

#include "Client.h"

Client::Client() : Process() {
    try {
        msgQueueQueries = Cola<dbQuery_t>(MSG_QUEUE_QUERIES_NAME, 'a');
        msgQueueResponses = Cola<dbResponse_t>(MSG_QUEUE_RESPONSES_NAME, 'a');
        clientId = getpid();
        Logger::logger().log("Client " + to_string(clientId) + " Initialized");
    }catch (MessageQueueException e){
        Logger::logger().log("Error initializing client:  " + to_string(clientId) + e.what());
    }
}


entryRow_t entryRowFromPersona(Persona &persona) {
    entryRow_t entryRow;
    strcpy(entryRow.direccion, persona.getDireccion().c_str());
    strcpy(entryRow.nombre, persona.getNombre().c_str());
    strcpy(entryRow.telefono, persona.getTelefono().c_str());

    return entryRow;
}

int Client::save(Persona &persona) {
    Logger::logger().log("Client " + to_string(clientId) + " Saving");

    if (!checkDBManager())
        return -1;

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    dbQuery.entryRow = entryRowFromPersona(persona);
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

Persona Client::getByName(string name) {
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving name " + name);

    Persona personaError = Persona("Err", "Err", "Err");

    if (!checkDBManager())
        return personaError;

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    strcpy(dbQuery.nombre, name.c_str());
    dbQuery.action = RETRIEVE;

    int result = msgQueueQueries.escribir(dbQuery);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/Query");
        return Persona("Err", "Err", "Err");
    }

    dbResponse_t dbResponse;
    result = msgQueueResponses.leer(clientId, &dbResponse);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/Response");
        return Persona("Err", "Err", "Err");
    }

    if (dbResponse.result < 0)
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/DB");
    else {
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve Successful");
        Persona persona = Persona::buildFromString(dbResponse.value);
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve " + persona.getStringRepresentation());
        return persona;
    }

    return Persona("Err", "Err", "Err");
}

//Throws InvalidParamsException if name is invalid
Persona Client::personaWithName(string &name) {
    return Persona(name, "", "");
}

bool Client::checkDBManager() {
    if (!msgQueueQueries.creadoCorrectamente() || !msgQueueResponses.creadoCorrectamente()) {
        Logger::logger().log("Client " + to_string(clientId) + " - Error: el DB Manager no esta levantado ");
        return false;
    }

    return true;
}