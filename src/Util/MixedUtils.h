//
// Created by fede on 15/06/15.
//

#ifndef CONCU_LUCAS_FEDE_TP2_MIXEDUTILS_H
#define CONCU_LUCAS_FEDE_TP2_MIXEDUTILS_H

#include <string>

using namespace std;

class MixedUtils {
public:
    static void padTo(std::string &str, const size_t num, const char paddingChar = ' ');
    static string rtrim(std::string &str);
};

#endif //CONCU_LUCAS_FEDE_TP2_MIXEDUTILS_H
