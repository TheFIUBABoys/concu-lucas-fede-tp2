//
// Created by fede on 13/06/15.
//

#include <string.h>
#include "Client.h"
#include "../../Exception/InvalidParamsException.h"

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

    Persona persona1 = Persona("Foo","Avenida del Foo","3-14159-2653");
    Persona persona2 = Persona("Bar","Avenida del Bar","2-7182-8182");

    save(persona1);
    save(persona2);

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

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    dbQuery.entryRow = entryRowFromPersona(persona);
    dbQuery.action = SAVE;

    int result = msgQueueQueries.escribir(dbQuery);
    if (result < 0) {
        Logger::logger().log("Client " + to_string(clientId) + " Error Saving/Persona");
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

Persona Client::updateByName(string name) {
    Logger::logger().log("Client " +  to_string(clientId) + " updating name " + name);
    Persona persona = personaWithName(name);

    //TODO - Update in from manager
    //Return updated persona
    return Persona("Err","Err","Err");
}

Persona Client::getByName(string name) {
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving name " + name );
    Persona persona = personaWithName(name);

    //TODO - Get from manager
    return Persona("Err","Err","Err");
}

//Returns deleted persona
Persona Client::deleteByName(string name) {
    Logger::logger().log("Client " + to_string(clientId) + " Deleting name " + name);

    Persona persona = personaWithName(name);
    //TODO - Get from manager
    return Persona("Err","Err","Err");

}

//Throws InvalidParamsException if name is invalid
Persona Client::personaWithName(string &name) {
    return Persona(name, "", "");
}