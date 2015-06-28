#ifndef COLA_H_
#define COLA_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>
#include "../../Exception/MessageQueueException.h"

template<class T>
class Cola {
private:


    key_t clave;
    int id;

public:
    Cola();

    Cola(const std::string &archivo, const char letra);

    ~Cola();

    int escribir(const T &dato) const;

    int leer(const int tipo, T *buffer) const;

    int destruir() const;

    bool creadoCorrectamente() const;
};

template<class T>
Cola<T>::Cola(const std::string &archivo, const char letra) {
    this->clave = ftok(archivo.c_str(), letra);
    if (this->clave == -1)
        throw MessageQueueException((string("Error en ftok: ")+ string(strerror(errno))).c_str());
    this->id = msgget(this->clave, 0666 | IPC_CREAT);
    if (this->id == -1)
        throw MessageQueueException((string("Error en msgget: ")+ string(strerror(errno))).c_str());

}

//To avoid initialization errors
template<class T>
Cola<T>::Cola() {
    this->clave = -1;
}

template<class T>
Cola<T>::~Cola() {
}

template<class T>
int Cola<T>::destruir() const {
    int resultado = msgctl(this->id, IPC_RMID, NULL);
    return resultado;
}

template<class T>
int Cola<T>::escribir(const T &dato) const {
    int resultado = msgsnd(this->id, static_cast<const void *>(&dato), sizeof(T) - sizeof(long), 0);
    if (resultado < 0)
        throw MessageQueueException((string("Error al escribir cola: ")+ string(strerror(errno))).c_str());
    return resultado;
}

template<class T>
bool Cola<T>::creadoCorrectamente() const {
    return (this->clave != -1);
}

template<class T>
int Cola<T>::leer(const int tipo, T *buffer) const {
    int resultado = (int) msgrcv(this->id, static_cast<void *>(buffer), sizeof(T) - sizeof(long), tipo, 0);
    return resultado;
}

#endif /* COLA_H_ */
