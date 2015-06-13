//
// Created by fede on 13/06/15.
//

#include "Client.h"

Client::Client() : Process() {
    Logger::logger().log("Client Initialized");
}

void Client::start() {
    Logger::logger().log("Client Running");
}