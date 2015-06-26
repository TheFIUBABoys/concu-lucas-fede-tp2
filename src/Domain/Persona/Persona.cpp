//
// Created by lucas on 6/14/15.
//

#include "Persona.h"

#define MAX_NOMBRE 61
#define MAX_DIR 120
#define MAX_TEL 13

void Persona::setDireccion(string direccion) {
   if (direccion.length()>MAX_DIR){
      throw InvalidParamsException(("El tamaño de direccion debe ser menor a " + to_string(MAX_DIR)).c_str());
   }else{
      this->direccion = direccion;
   }
}

void Persona::setTelefono(string telefono) {
   if (telefono.length()>MAX_TEL){
      throw InvalidParamsException(("El tamaño de telefono debe ser menor a " + to_string(MAX_TEL)).c_str());
   }else{
      this->telefono = telefono;
   }
}

void Persona::setNombre(string nombre) {
   if (nombre.length()>MAX_NOMBRE){
      throw InvalidParamsException(("El tamaño de nombre debe ser menor a " + to_string(MAX_NOMBRE)).c_str());
   }else{
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

string Persona::getStringRepresentation() {
   string nombreTmp = string(this->nombre);
   string direccionTmp = string(this->direccion);
   string telefonoTmp = string(this->telefono);
   MixedUtils::padTo(nombreTmp, NOMBRE_SIZE - 1);
   MixedUtils::padTo(direccionTmp, DIRECCION_SIZE - 1);
   MixedUtils::padTo(telefonoTmp, TELEFONO_SIZE - 1);

   return nombreTmp + direccionTmp + telefonoTmp;
}

Persona Persona::buildFromString(string data) {
   string nombre = data.substr(0, NOMBRE_SIZE - 1);
   string direccion = data.substr(NOMBRE_SIZE - 1, DIRECCION_SIZE - 1);
   string telefono = data.substr(NOMBRE_SIZE + DIRECCION_SIZE - 2, TELEFONO_SIZE - 1);

   nombre = MixedUtils::rtrim(nombre);
   direccion = MixedUtils::rtrim(direccion);
   telefono = MixedUtils::rtrim(telefono);

   return Persona(nombre, direccion, telefono);
}