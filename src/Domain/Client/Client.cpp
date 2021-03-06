//
// Created by fede on 13/06/15.
//

#include "Client.h"
#include "../../Exception/DBException/DBException.h"

static Client *signal_object;

void signal_handler(int signum) {
    signal_object->handleSignal(signum);
}

void Client::handleSignal(int signum) {
    if (signum == SIGINT) {
        shouldQuit = true;
        bool oldDebug =  Logger::logger().debug;
        Logger::logger().debug = true;
        Logger::logger().log("Client Received signal " + to_string(signum));
        Logger::logger().debug = oldDebug;
    }
}

Client::Client() {
    try {
        shouldQuit = false;
        msgQueueQueries = Cola<dbQuery_t>(MSG_QUEUE_QUERIES_NAME, 'a');
        msgQueueResponses = Cola<dbResponse_t>(MSG_QUEUE_RESPONSES_NAME, 'a');
        clientId = getpid();
        signal_object = this;
        signal(SIGINT, signal_handler);
        Logger::logger().log("Client " + to_string(clientId) + " Initialized");
    } catch (MessageQueueException e) {
        Logger::logger().log("Error initializing client:  " + to_string(clientId) + e.what());
    }
}

ClientResponse Client::save(Persona &persona) {
    Logger::logger().log("Client " + to_string(clientId) + " Saving");

    if (!checkDBManager())
        return ClientResponseError;

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    dbQuery.entryRow = persona.getEntryRow();
    dbQuery.action = SAVE;

    if (!shouldQuit) {
        int result = msgQueueQueries.escribir(dbQuery);
        if (result < 0) {
            Logger::logger().log("Client " + to_string(clientId) + " Error Saving/Query");
            return ClientResponseError;
        }
    }
    dbResponse_t dbResponse;
    dbResponse.result = ResponseTypeError;
    if (!shouldQuit) {
        int result = msgQueueResponses.leer(clientId, &dbResponse);
        if (result < 0) {
            Logger::logger().log("Client " + to_string(clientId) + " Error Saving/Response");
            return ClientResponseError;
        }
    }

    if (dbResponse.result == ResponseTypeError) {
        string message = "Client " + to_string(clientId) + " Error Saving/DB";
        Logger::logger().log(message);
        return ClientResponseError;
    } else {
        if (dbResponse.result == ResponseTypeAlreadyExists) {
            string message = "Client " + to_string(clientId) + " tried to save repeated persona";
            Logger::logger().log(message);
            return ClientResponseRepeated;
        } else {
            Logger::logger().log("Client " + to_string(clientId) + " Saving Successful");
        }
    }
    return ClientResponseOK;
}

Persona Client::getByName(string name) {
    Logger::logger().log("Client " + to_string(clientId) + " Retrieving name " + name);

    if (!checkDBManager()) {
        string message = "DBManager is offline";
        Logger::logger().log(message);
        throw DBException(message.c_str());
    }

    dbQuery_t dbQuery;
    dbQuery.mtype = clientId;
    strcpy(dbQuery.nombre, name.c_str());
    dbQuery.action = RETRIEVE;
    if (!shouldQuit) {
        int result = msgQueueQueries.escribir(dbQuery);
        if (result < 0) {
            string message = "Client " + to_string(clientId) + " Error Writing query to message queue";
            Logger::logger().log(message);
            throw DBException(message.c_str());
        }
    }

    dbResponse_t dbResponse;
    dbResponse.result = ResponseTypeError;
    if (!shouldQuit) {
        int result = msgQueueResponses.leer(clientId, &dbResponse);
        if (result < 0) {
            string message = "Client " + to_string(clientId) + " Error reading response from message queue";
            Logger::logger().log(message);
            throw DBException(message.c_str());
        }
    }

    if (dbResponse.result == ResponseTypeError) {
        string message = "Client " + to_string(clientId) + " response came with an error";
        Logger::logger().log(message);
        throw DBException(message.c_str());
    } else {
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve Successful");
        Persona persona = Persona(dbResponse.entryRow);
        Logger::logger().log("Client " + to_string(clientId) + " Retrieve " + persona.getStringRepresentation());
        return persona;
    }
}

bool Client::checkDBManager() {
    return !(!msgQueueQueries.creadoCorrectamente() || !msgQueueResponses.creadoCorrectamente());
}