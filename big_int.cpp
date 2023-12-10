//
// Created by hechu on 23-11-21.
//

#include "big_int.h"

std::ostream &operator<<(std::ostream &out, const big_int &b) {
    out << to_string(b, false);
    return out;
}

std::istream &operator>>(std::istream &in, big_int &b) {
    std::string s;
    in >> s;
    b = big_int(s);
    return in;
}

std::string to_string(big_int b, bool split) {
    return b.to_string(split);
}

std::string to_string(big_int b) {
    return to_string(b, false);
}

big_int &operator+=(big_int &a, const big_int &b) {
    a = a + b;
    return a;
}

big_int &operator-=(big_int &a, const big_int &b) {
    a = a - b;
    return a;
}

big_int &operator*=(big_int &a, const big_int &b) {
    a = a * b;
    return a;
}

big_int &operator/=(big_int &a, const big_int &b) {
    a = a / b;
    return a;
}

big_int pow(const big_int &a, const int &index) {
    if (index < 0)
        throw "index must bigger than zero";
    big_int c = 1;
    for (auto i = 0; i < index; i++) {
        c *= a;
    }
    return c;
}
