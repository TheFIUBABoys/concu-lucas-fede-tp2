//
// Created by lucas on 6/14/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_QUERY_H
#define CONCU_LUCAS_FEDE_TP2_QUERY_H

#define SEPARATOR_CHARACTER ";"

#include <string>
#include "../EntryRow/entryRow.h"
#include "../../Exception/InvalidParamsException.h"

using namespace std;
class Persona {
public:
    Persona(string nombre, string direccion, string telefono);
    Persona(entryRow_t entryRow);
    static Persona buildFromString(string data);
    void setNombre(string nombre);
    void setTelefono(string telefono);
    void setDireccion(string direccion);
    string getNombre();
    string getDireccion();
    string getTelefono();
    string getStringRepresentation();
    entryRow_t getEntryRow();
    friend bool operator==(const Persona &lhs, const Persona &rhs) {
        return (lhs.nombre == rhs.nombre) && (lhs.direccion == rhs.direccion) && (lhs.telefono == rhs.telefono);
    }

    friend bool operator!=(const Persona &lhs, const Persona &rhs) {
        return (lhs.nombre != rhs.nombre) || (lhs.direccion != rhs.direccion) || (lhs.telefono != rhs.telefono);

    }
private:
    string nombre, direccion, telefono;
};


#endif //CONCU_LUCAS_FEDE_TP2_QUERY_H
