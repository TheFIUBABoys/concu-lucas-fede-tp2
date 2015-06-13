#include <iostream>
#include "src/Domain/Client/Client.h"
#include "src/Domain/DatabaseManager/DatabaseManager.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Client client = Client();
    client.start();

    DatabaseManager dbManager = DatabaseManager();
    dbManager.start();

    return 0;
}