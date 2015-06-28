//
// Created by lucas on 6/28/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_MESSAGEQUEUEEXCEPTION_H
#define CONCU_LUCAS_FEDE_TP2_MESSAGEQUEUEEXCEPTION_H
#include <exception>
#include <string>
using namespace std;
class MessageQueueException : public exception {
private:
    string err_msg;
public:
    MessageQueueException(const char *msg) : err_msg(msg) {};
    ~MessageQueueException() throw() {};
    const char *what() const throw() { return this->err_msg.c_str(); };
};


#endif //CONCU_LUCAS_FEDE_TP2_MESSAGEQUEUEEXCEPTION_H
