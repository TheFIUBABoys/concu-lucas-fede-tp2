//
// Created by lucas on 6/14/15.
//

#include <string.h>
#include <iostream>
#include "Persona.h"

#define MAX_NOMBRE 61
#define MAX_DIR 120
#define MAX_TEL 13

void Persona::setDireccion(string direccion) {
    if (direccion.length() > MAX_DIR) {
        throw InvalidParamsException(("El tamaño de direccion debe ser menor a " + to_string(MAX_DIR)).c_str());
    } else {
        this->direccion = direccion;
    }
}

void Persona::setTelefono(string telefono) {
    if (telefono.length() > MAX_TEL) {
        throw InvalidParamsException(("El tamaño de telefono debe ser menor a " + to_string(MAX_TEL)).c_str());
    } else {
        this->telefono = telefono;
    }
}

void Persona::setNombre(string nombre) {
    if (nombre.length() > MAX_NOMBRE) {
        throw InvalidParamsException(("El tamaño de nombre debe ser menor a " + to_string(MAX_NOMBRE)).c_str());
    } else {
        this->nombre = nombre;
    }
}

string Persona::getNombre() {
    return this->nombre;
}

string Persona::getDireccion() {
    return this->direccion;
}

string Persona::getTelefono() {
    return this->telefono;
}

Persona::Persona(string nombre, string direccion, string telefono) {
    setNombre(nombre);
    setDireccion(direccion);
    setTelefono(telefono);
}

Persona::Persona(entryRow_t entryRow) {
    setNombre(entryRow.nombre);
    setDireccion(entryRow.direccion);
    setTelefono(entryRow.telefono);
}

string Persona::getStringRepresentation() {
    string nombreTmp = string(this->nombre);
    string direccionTmp = string(this->direccion);
    string telefonoTmp = string(this->telefono);

    return this->nombre + SEPARATOR_CHARACTER + this->direccion + SEPARATOR_CHARACTER + this->telefono;
}

Persona Persona::buildFromString(string data) {
    size_t indexNombre = data.find(SEPARATOR_CHARACTER, 0);
    size_t indexDireccion = data.find(SEPARATOR_CHARACTER, indexNombre + 1);

    string nombre = data.substr(0, indexNombre);
    string direccion = data.substr(indexNombre + 1, indexDireccion - indexNombre - 1);
    string telefono = data.substr(indexDireccion + 1);

    return Persona(nombre, direccion, telefono);
}

entryRow_t Persona::getEntryRow() {
    entryRow_t entryRow;
    strcpy(entryRow.direccion, getDireccion().c_str());
    strcpy(entryRow.nombre, getNombre().c_str());
    strcpy(entryRow.telefono, getTelefono().c_str());

    return entryRow;
}
