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

    /*Persona persona1 = Persona("Foo","Avenida del Foo","3-14159-2653");
    Persona persona2 = Persona("Bar","Avenida del Bar","2-7182-8182");

    save(persona1);
    save(persona2);

    getByName( persona1.getNombre() );
    getByName( persona2.getNombre() );*/

    // GracefulQuit
    Logger::logger().log("Client " + to_string(clientId) + " Quit");
}


entryRow_t entryRowFromPersona(Persona& persona){
    entryRow_t entryRow;
    strcpy(entryRow.direccion, persona.getDireccion().c_str());
    strcpy(entryRow.nombre, persona.getNombre().c_str());
    strcpy(entryRow.telefono, persona.getTelefono().c_str());

    return entryRow;
}

int Client::save(Persona& persona) {
    Logger::logger().log("Client " + to_string(clientId) + " Saving");

    if (checkDBManager() == false)
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
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving name " + name );

    Persona personaError = Persona("Err","Err","Err");

    if (checkDBManager() == false)
        return personaError;

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    strcpy(dbQuery.nombre, name.c_str());
    dbQuery.action = RETRIEVE;

    int result = msgQueueQueries.escribir(dbQuery);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/Query");
        return Persona("Err","Err","Err");
    }

    dbResponse_t dbResponse;
    result = msgQueueResponses.leer(clientId, &dbResponse);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/Response");
        return Persona("Err","Err","Err");
    }

    if (dbResponse.result < 0)
        Logger::logger().log("Client " + to_string(clientId) + " Error Retrieving/DB");
    else {
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve Successful");
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve " + dbResponse.value);
        return Persona::buildFromString(dbResponse.value);
    }

    return Persona("Err","Err","Err");
}

//Throws InvalidParamsException if name is invalid
Persona Client::personaWithName(string &name) {
    return Persona(name, "", "");
}

bool Client::checkDBManager() {
    if (msgQueueQueries.creadoCorrectamente() == false || msgQueueResponses.creadoCorrectamente() == false) {
        Logger::logger().log("Client " + to_string(clientId) + " - Error: el DB Manager no esta levantado ");
        return false;
    }

    return true;
}