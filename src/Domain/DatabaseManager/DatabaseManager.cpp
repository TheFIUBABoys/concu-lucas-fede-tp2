//
// Created by fede on 13/06/15.
//

#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : Process() {
    Logger::logger().log("DatabaseManager Initialized");
}

void DatabaseManager::start() {
    Logger::logger().log("DatabaseManager Running");
}