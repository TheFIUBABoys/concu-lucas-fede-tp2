//
// Created by fede on 15/06/15.
//

#include "MixedUtils.h"

void MixedUtils::padTo(std::string &str, const size_t num, const char paddingChar) {
    if(num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}

// trim from end
string MixedUtils::rtrim(string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');

    return str.substr(first, (last-first+1));
}