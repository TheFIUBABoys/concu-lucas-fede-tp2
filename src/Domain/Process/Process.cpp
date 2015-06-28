//
// Created by fede on 09/05/15.
//

#include "Process.h"

Process::Process() {
    SignalHandler::getInstance()->registrarHandler ( SIGINT,&sigint_handler);
}