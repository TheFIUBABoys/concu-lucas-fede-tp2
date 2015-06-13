#include <iostream>
#include <fstream>
#include "src/Domain/Client/Client.h"
#include "src/Domain/DatabaseManager/DatabaseManager.h"

using namespace std;

void createTempfiles() {//Creating temp lock files
    ofstream myfile;
    myfile.open(MSG_QUEUE_NAME);
    myfile.close();
}

int main() {
    cout << "Hello, World!" << endl;

    createTempfiles();

    Client client = Client();
    client.start();

    DatabaseManager dbManager = DatabaseManager();
    dbManager.start();

    return 0;
}