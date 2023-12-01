//
// Created by hechu on 23-12-1.
//

#include "expression.h"
#include <string>

std::istream &operator>>(std::istream &in, expression &b) {
    std::string s;
    getline(in, s);
    b = expression(s);
    return in;
}
