//
// Created by lucas on 6/14/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_QUERY_H
#define CONCU_LUCAS_FEDE_TP2_QUERY_H

#include <string>
#include "../EntryRow/entryRow.h"
#include "../../Exception/InvalidParamsException.h"
#include "../../Util/MixedUtils.h"

using namespace std;
class Persona {
public:
    Persona(string nombre, string direccion, string telefono);
    Persona buildFromString(string data);
    void setNombre(string nombre);
    void setTelefono(string telefono);
    void setDireccion(string direccion);
    string getNombre();
    string getDireccion();
    string getTelefono();
    string getStringRepresentation();
private:
    string nombre, direccion, telefono;
};


#endif //CONCU_LUCAS_FEDE_TP2_QUERY_H
