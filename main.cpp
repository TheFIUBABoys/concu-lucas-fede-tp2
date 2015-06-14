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

int testSave(Client &client) {
    return -1;
}

int testUpdate(Client &client) {
    return -1;
}

int testDelete(Client &client) {
    return -1;
}

int testGet(Client &client) {
    return -1;
}


int main() {
    createTempfiles();
    if (fork() == 0) {
        Client client = Client();
        //testSave(client) < 0 ? Logger::logger().log("TEST SAVE FAILED") : Logger::logger().log("TEST SAVE OK");
        //testGet(client) < 0 ? Logger::logger().log("TEST GET FAILED") : Logger::logger().log("TEST GET OK");
        //testDelete(client) < 0 ? Logger::logger().log("TEST DELETE FAILED") : Logger::logger().log("TEST DELETE OK");
        //testUpdate(client) < 0 ? Logger::logger().log("TEST UPDATE FAILED") : Logger::logger().log("TEST UPDATE OK");

        client.start();

        Logger::logger().log("Exiting client");

    } else {
        DatabaseManager dbManager = DatabaseManager();
        dbManager.start();
        Logger::logger().log("Exiting server");

    }

    return 0;
}