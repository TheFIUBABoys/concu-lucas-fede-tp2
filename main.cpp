#include <iostream>
#include <fstream>
#include <vector>
#include <wait.h>
#include "src/Domain/Client/Client.h"
#include "src/Domain/DatabaseManager/DatabaseManager.h"
#include "src/Exception/DBException/DBException.h"

using namespace std;

typedef enum ConcurrentTestResult {
    ConcurrentTestResultOK,
    ConcurrentTestResultError,
    ConcurrentTestResultChild
} ProcessType;

void createTempfiles() {
    //Creating temp lock files
    ofstream myfile;
    myfile.open(MSG_QUEUE_QUERIES_NAME);
    myfile.close();
    myfile.open(MSG_QUEUE_RESPONSES_NAME);
    myfile.close();
    myfile.close();
}


bool testSave(Client &client) {
    Logger::logger().debug = false;
    remove(PERSISTENCE_FILE);   // Reset persistence
    try {
        Persona persona1 = Persona("Foo", "Avenida del Foo", "3-14159-2653");
        client.save(persona1);
        string line;
        ifstream persistenceFile(PERSISTENCE_FILE);
        getline(persistenceFile, line);
        Persona persona2 = Persona::buildFromString(line);
        Logger::logger().debug = true;
        return (persona1 == persona2);
    } catch (DBException e) {
        return false;
    }
}


bool testSaveWithSameName(Client &client) {
    try {
        Logger::logger().debug = false;
        remove(PERSISTENCE_FILE);   // Reset persistence
        Persona persona1 = Persona("Foo", "Avenida del Foo", "3-14159-2653");
        client.save(persona1);
        Persona persona2 = Persona("Foo", "Avenidaasd del Foo", "3-149-2653");
        ClientResponse response = client.save(persona2);
        Logger::logger().debug = true;
        return response == ClientResponseRepeated;
    } catch (DBException e) {
        return false;
    }
}

bool testRetrieve(Client &client) {
    try {
        Logger::logger().debug = false;
        remove(PERSISTENCE_FILE);   // Reset persistence
        Persona persona1 = Persona("Foo", "Avenida del Foo", "3-1459-2653");
        client.save(persona1);
        Persona personaRetrieved = client.getByName(persona1.getNombre());
        Logger::logger().debug = true;
        return (persona1 == personaRetrieved);
    } catch (DBException e) {
        return false;
    }
}

bool testRetrieveNotFound(Client &client) {
    Logger::logger().debug = false;
    remove(PERSISTENCE_FILE);   // Reset persistence
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-1459-2653");
    try {
        client.getByName(persona1.getNombre());
        Logger::logger().debug = true;
        return false;
    } catch (DBException e) {
        Logger::logger().debug = true;
        return true;
    }
}

bool testBulkSaveAndRetrieve(Client &client) {
    try {
        Logger::logger().debug = false;
        remove(PERSISTENCE_FILE);   // Reset persistence
        vector<Persona> v;
        for (int i = 0; i < 1000; i++) {
            Persona persona1 = Persona("Foo" + to_string(i), "Avenida del Foo", "3-14159-2653");
            v.push_back(persona1);
            client.save(persona1);
        }
        bool success = true;
        for (int i = 0; i < 1000; i++) {
            Persona personaRetrieved = client.getByName("Foo" + to_string(i));
            if (v[i] != personaRetrieved) {
                Logger::logger().debug = true;
                Logger::logger().log("Error comparing Personas");
                Logger::logger().log(v[i].getStringRepresentation());
                Logger::logger().log(personaRetrieved.getStringRepresentation());
                success = false;
                break;
            }
        }
        Logger::logger().debug = true;
        return success;
    } catch (DBException e) {
        return false;
    }
}

ConcurrentTestResult testConcurrentSaves() {
    try {
        Logger::logger().debug = false;
        remove(PERSISTENCE_FILE);   // Reset persistence

        int processes = 100;
        for (int i = 0; i < processes; i++) {
            __pid_t pid = fork();
            if (pid == 0) {
                try {
                    Client client = Client();
                    Persona persona1 = Persona("Foo" + to_string(i), "Avenida del Foo" + to_string(i), to_string(i));
                    client.save(persona1);
                    return ConcurrentTestResultChild;
                } catch (DBException e) {
                    return ConcurrentTestResultChild;
                }
            }
        }
        for (int i = 0; i < processes; i++) {
            Logger::logger().log("ASD");
            wait(NULL);
        }

        bool success = true;
        for (int i = 0; i < processes; i++) {
            Client client = Client();
            try {
                client.getByName("Foo" + to_string(i));
            } catch (DBException e) {
                success = false;
                break;
            }
        }
        Logger::logger().debug = true;
        return success ? ConcurrentTestResultOK : ConcurrentTestResultError;
    } catch (DBException e) {
        return ConcurrentTestResultError;
    }
}


void clienteInteractivo() {
    remove(PERSISTENCE_FILE);   // Reset persistence

    Client client = Client();   // Se crea cliente

    // Se declaran algunas personas para guardar
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-14159-2653");
    Persona persona2 = Persona("Bar", "Avenida del Bar", "2-71828-1828");
    Persona persona3 = Persona("Baz", "Avenida del Baz", "1-61803-3988");


    client.save(persona1);  // Se guarda la persona 1
    client.save(persona3);  // Se guarda la persona 3

    // Se corrobora que no se pueda encontrar la persona 2
    try {
        Persona personaRetrieved = client.getByName(persona2.getNombre());
    } catch (DBException e) {
        Logger::logger().log("Persona 2 no encontrada");
    }

    // Se hace un retrieve para la persona 1
    Persona personaRetrieved = client.getByName(persona1.getNombre());
    if (personaRetrieved == persona1) {
        Logger::logger().log("Persona1 encontrada");
    }

}

//Tests
int main() {
    if (fork() == 0) {
        sleep(1);   // Simular que el cliente se abre despues que el dbManager

        // clienteInteractivo();

        Client client = Client();
        testSave(client) ? Logger::logger().log("TEST SAVE OK") : Logger::logger().log("TEST SAVE FAILED");
        testSaveWithSameName(client) ? Logger::logger().log("TEST SAVE REPEATED OK") : Logger::logger().log(
                "TEST SAVE REPEATED FAILED");
        testRetrieve(client) ? Logger::logger().log("TEST RETRIEVE OK") : Logger::logger().log("TEST RETRIEVE FAILED");
        testRetrieveNotFound(client) ? Logger::logger().log("TEST RETRIEVE NOT FOUND OK") : Logger::logger().log(
                "TEST RETRIEVE NOT FOUND FAILED");
        testBulkSaveAndRetrieve(client) ? Logger::logger().log("TEST BULK RETRIEVE OK") : Logger::logger().log(
                "TEST BULK RETRIEVE FAILED");
        ConcurrentTestResult concurrentTestResult = testConcurrentSaves();

        if (concurrentTestResult == ConcurrentTestResultOK) {
            Logger::logger().log("TEST CONCURRENT SAVES OK");
        } else {
            if (concurrentTestResult == ConcurrentTestResultError) {
                Logger::logger().log("TEST CONCURRENT SAVES FAILED");
            } else {
                //Childs
                return 0;
            }
        }
        Logger::logger().log("Exiting client");
    } else {
        // Se crea el Database Manager

        createTempfiles();
        DatabaseManager dbManager = DatabaseManager();
        Logger::logger().debug = false;
        dbManager.start();
        Logger::logger().debug = true;
        Logger::logger().log("Exiting server");
    }
    return 0;
}
