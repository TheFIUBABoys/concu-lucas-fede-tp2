#include <iostream>
#include <fstream>
#include "src/Domain/Client/Client.h"
#include "src/Domain/DatabaseManager/DatabaseManager.h"

using namespace std;

void createTempfiles() {//Creating temp lock files
    ofstream myfile;
    myfile.open(MSG_QUEUE_QUERIES_NAME);
    myfile.close();
    myfile.open(MSG_QUEUE_RESPONSES_NAME);
    myfile.close();
    myfile.open(SHARED_MEM_CLIENT_ID);
    myfile.close();
}

bool testSave(Client &client) {
    remove(PERSISTENCE_FILE);   // Reset persistence

    Persona persona1 = Persona("Foo","Avenida del Foo","3-14159-2653");

    client.save(persona1);

    string line;
    ifstream persistenceFile(PERSISTENCE_FILE);
    getline(persistenceFile, line);

    return (persona1.getStringRepresentation().compare(line) == 0);
}

bool testRetrieve(Client &client) {
    remove(PERSISTENCE_FILE);   // Reset persistence

    Persona persona1 = Persona("Foo","Avenida del Foo","3-14159-2653");

    client.save(persona1);

    Persona personaRetrieved = client.getByName(persona1.getNombre());

    return (persona1.getStringRepresentation().compare( personaRetrieved.getStringRepresentation() ) == 0);
}


int main() {
    if (fork() == 0) {
        sleep(2);   // Simular que el cliente se abre despues que el dbManager
        Client client = Client();
        testSave(client) ? Logger::logger().log("TEST SAVE OK") : Logger::logger().log("TEST SAVE FAILED");
        testRetrieve(client) ? Logger::logger().log("TEST RETRIEVE OK") : Logger::logger().log("TEST RETRIEVE FAILED");

        client.start();

        Logger::logger().log("Exiting client");

    } else {
        createTempfiles();

        DatabaseManager dbManager = DatabaseManager();
        dbManager.start();
        Logger::logger().log("Exiting server");

    }

    return 0;
}