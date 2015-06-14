//
// Created by lucas on 6/14/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_INVALIDPARAMSEXCEPTION_H
#define CONCU_LUCAS_FEDE_TP2_INVALIDPARAMSEXCEPTION_H

#include <exception>
#include <string>

using namespace std;
class InvalidParamsException : public exception {
private:
    string err_msg;
public:
    InvalidParamsException(const char *msg) : err_msg(msg) {};
    ~InvalidParamsException() throw() {};
    const char *what() const throw() { return this->err_msg.c_str(); };
};


#endif //CONCU_LUCAS_FEDE_TP2_INVALIDPARAMSEXCEPTION_H
