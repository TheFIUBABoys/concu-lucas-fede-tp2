//
// Created by lucas on 6/28/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_DBEXCEPTION_H
#define CONCU_LUCAS_FEDE_TP2_DBEXCEPTION_H


#include <exception>
#include <string>
using namespace std;
class DBException : public exception {
private:
    string err_msg;
public:
    DBException(const char *msg) : err_msg(msg) {};
    ~DBException() throw() {};
    const char *what() const throw() { return this->err_msg.c_str(); };
};


#endif //CONCU_LUCAS_FEDE_TP2_DBEXCEPTION_H
