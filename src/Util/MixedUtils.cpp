//
// Created by fede on 15/06/15.
//

#include "MixedUtils.h"

void MixedUtils::padTo(std::string &str, const size_t num, const char paddingChar) {
    if(num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}