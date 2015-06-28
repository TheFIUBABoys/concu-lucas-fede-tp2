#include <iostream>
#include <fstream>
#include <vector>
#include "src/Domain/Client/Client.h"
#include "src/Domain/DatabaseManager/DatabaseManager.h"
#include "src/Exception/DBException/DBException.h"

using namespace std;

void createTempfiles() {//Creating temp lock files
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
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-14159-2653");
    client.save(persona1);
    string line;
    ifstream persistenceFile(PERSISTENCE_FILE);
    getline(persistenceFile, line);
    Persona persona2 = Persona::buildFromString(line);
    Logger::logger().debug = true;
    return (persona1 == persona2);
}


bool testSaveWithSameName(Client &client) {
    Logger::logger().debug = false;
    remove(PERSISTENCE_FILE);   // Reset persistence
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-14159-2653");
    client.save(persona1);
    Persona persona2 = Persona("Foo", "Avenidaasd del Foo", "3-149-2653");
    ClientResponse response = client.save(persona2);
    Logger::logger().debug = true;
    return response==ClientResponseRepeated;
}

bool testRetrieve(Client &client) {
    Logger::logger().debug = false;
    remove(PERSISTENCE_FILE);   // Reset persistence
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-1459-2653");
    client.save(persona1);
    Persona personaRetrieved = client.getByName(persona1.getNombre());
    Logger::logger().debug = true;
    return (persona1 == personaRetrieved);
}

bool testRetrieveNotFound(Client &client) {
    Logger::logger().debug = false;
    remove(PERSISTENCE_FILE);   // Reset persistence
    Persona persona1 = Persona("Foo", "Avenida del Foo", "3-1459-2653");
    try {
        Persona personaRetrieved = client.getByName(persona1.getNombre());
        Logger::logger().debug = true;
        return false;
    }catch (DBException e){
        Logger::logger().debug = true;
        return true;
    }
}

bool testBulkSaveAndRetrieve(Client &client) {
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
}


//Tests
int main() {
    if (fork() == 0) {
        sleep(1);   // Simular que el cliente se abre despues que el dbManager
        Client client = Client();
        testSave(client) ? Logger::logger().log("TEST SAVE OK") : Logger::logger().log("TEST SAVE FAILED");
        testSaveWithSameName(client) ? Logger::logger().log("TEST SAVE REPEATED OK") : Logger::logger().log("TEST SAVE REPEATED FAILED");
        testRetrieve(client) ? Logger::logger().log("TEST RETRIEVE OK") : Logger::logger().log("TEST RETRIEVE FAILED");
        testRetrieveNotFound(client) ? Logger::logger().log("TEST RETRIEVE NOT FOUND OK") : Logger::logger().log("TEST RETRIEVE NOT FOUND FAILED");
        testBulkSaveAndRetrieve(client) ? Logger::logger().log("TEST BULK RETRIEVE OK") : Logger::logger().log("TEST BULK RETRIEVE FAILED");
        Logger::logger().log("Exiting client");
    } else {
        Logger::logger().debug = false;
        createTempfiles();
        DatabaseManager dbManager = DatabaseManager();
        dbManager.start();
        Logger::logger().log("Exiting server");
    }
    return 0;
}


//Tests