//
// Created by fede on 13/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_CLIENT_H
#define CONCU_LUCAS_FEDE_TP2_CLIENT_H

#include "../Process/Process.h"
#include "../../Util/Logger/Logger.h"

class Client : Process {
public:
    Client();
    void start();
};

#endif //CONCU_LUCAS_FEDE_TP2_CLIENT_H
