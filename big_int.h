//
// Created by hechu on 23-11-21.
//

#ifndef INTEGER_CALCULATOR_BIG_INT_H
#define INTEGER_CALCULATOR_BIG_INT_H

#include "double_circular_linked_list.h"
#include "string"

class big_int : public double_circular_linked_list<short> {
public:

    friend std::istream &operator>>(std::istream &in, big_int &b);

    friend std::ostream &operator<<(std::ostream &out, const big_int &b);

    friend std::string to_string(big_int b, bool split);

    friend std::string to_string(big_int b);

    friend big_int &operator+=(big_int &a, const big_int &b);

    friend big_int &operator-=(big_int &a, const big_int &b);

    big_int() : double_circular_linked_list<short>() {
        head->value = 0;
    }

    big_int(size_t num) : big_int() {
        short r = 0;
        do {
            r = (short) (num % 10000);
            num /= (size_t) 10000;
            insert(r);
        } while (num != 0 || r != 0);
    }

    explicit big_int(const std::string &str) : big_int() {
        get_big_int_in(str, *this);
    }

    [[nodiscard]] big_int clone() const {
        return *new big_int(this->to_string());
    }

    [[nodiscard]] std::string to_string(bool split = false) const {
        std::string s;
        for (const auto &i: *this) {
            for (short j = 10000; j > 1; j /= 10) {
                s += std::to_string((int) (i % j) / (j / 10));
            }
            if (split)
                s += ",";
        }
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '0') {
                if (i == s.length() - 1) {
                    s = s.substr(i);
                    break;
                } else
                    continue;
            }
            s = s.substr(i);
            break;
        }
        if (isMinus && s != "0")
            s.insert(0, "-");
        return s;
    }

    //从字符串中读取big_int，返回读取结束的位置
    static size_t get_big_int_in(std::string si, big_int &bi) {
        if (si.empty()) return 0;
        size_t pos;
        std::string fixedStr = si;
        auto minus = false;
        for (auto i = 0; i < si.length(); i++) {
            auto c = si[i];
            if (c != '-') {
                fixedStr = si.substr(i);
                pos = i;
                break;
            }
            minus = !minus;
        }
        bi.isMinus = minus;
        for (auto i = 0; i <= fixedStr.length(); i++) {
            auto c = fixedStr[i];
            if (i == fixedStr.length() || !((c >= '0' && c <= '9') || c == ',')) {
                fixedStr = fixedStr.substr(0, i);
                pos += i;
                break;
            }
        }
        for (auto i = 0; i < fixedStr.length();) {
            auto c = fixedStr[i];
            if (c == ',') {
                fixedStr.erase(i, 1);
            } else
                i++;
        }
        auto headLength = fixedStr.length() % 4;
        headLength = headLength == 0 ? 4 : headLength;
        for (size_t i = 0; i < fixedStr.length(); i += i == 0 ? headLength : 4) {
            auto s = i == 0 ? fixedStr.substr(0, headLength) : fixedStr.substr(i, 4);
            if (s.length() == 0) break;
            auto v = (short) std::stoi(s);
            bi.insert(v, -1);
        }
        return pos;
    }

    //获取数字作为十进制数的位数
    size_t get_number_length() {
        auto a = this->clone();
        a.isMinus = false;
        return a.to_string().length();
    }

    [[nodiscard]] int compare_to(const big_int &b) const {
        if (!this->isMinus) {
            if (!b.isMinus) {
                if (this->node_count() > b.node_count())
                    return 1;
                if (this->node_count() < b.node_count())
                    return -1;

                auto n = this->head->next;
                auto m = b.head->next;
                while (n != this->head && m != b.head) {
                    if (n->value > m->value)
                        return 1;
                    if (n->value < m->value)
                        return -1;

                    n = n->next;
                    m = m->next;
                }
                return 0;
            } else
                return 1;
        } else {
            if (!b.isMinus) {
                return -1;
            } else
                return -(-*this).compare_to(-b);
        }
    }

    bool operator<(const big_int &ob) const {
        return this->compare_to(ob) < 0;
    }

    bool operator>(const big_int &ob) const {
        return this->compare_to(ob) > 0;
    }

    bool operator==(const big_int &ob) const {
        return this->compare_to(ob) == 0;
    }

    bool operator<=(const big_int &ob) const {
        return this->compare_to(ob) <= 0;
    }

    bool operator>=(const big_int &ob) const {
        return this->compare_to(ob) >= 0;
    }

    big_int operator+(const big_int &ob) const {
        auto a = big_int(this->to_string());
        auto b = big_int(ob.to_string());
        if (!this->isMinus) {
            if (!b.isMinus) {
                if (a.compare_to(b) < 0)
                    return b + a;
                auto currA = a.head->prev;
                auto currB = b.head->prev;
                short carryOver = 0;
                while (currB != b.head || carryOver != 0) {
                    if (currA == a.head) {
                        a.insert(0);
                        currA = currA->next;
                    }
                    short v = currA->value;
                    v += (currB == b.head ? 0 : currB->value) + carryOver;
                    currA->value = v % 10000;
                    carryOver = v / 10000;
                    currA = currA->prev;
                    currB = currB == b.head ? currB : currB->prev;
                }
                return a;
            } else
                return a - (-b);
        } else {
            if (!b.isMinus) {
                return b - (-a);
            } else {
                return -((-a) + (-b));
            }
        }
    }

    big_int operator-() const {
        auto a = this->clone();
        a.isMinus = !a.isMinus;
        return a;
    }

    big_int operator-(const big_int &ob) const {
        auto a = this->clone();
        auto b = ob.clone();
        if (!a.isMinus) {
            if (!b.isMinus) {
                auto d = a.compare_to(b);
                if (d > 0) {
                    auto currA = a.head->prev;
                    auto currB = b.head->prev;
                    short carryOver = 0;
                    while (currB != b.head || carryOver != 0) {
                        if (currA == a.head) {
                            a.insert(0);
                            currA = currA->next;
                        }
                        short v = currA->value;
                        v = v - currB->value + carryOver;
                        carryOver = 0;
                        while (v < 0) {
                            v += 10000;
                            carryOver -= 1;
                        }
                        currA->value = v % 10000;
                        currA = currA->prev;
                        currB = currB == b.head ? currB : currB->prev;
                    }
                    return a;
                }
                if (d < 0)
                    return -(b - a);
                if (d == 0)
                    return 0;
            } else
                return a + (-b);
        } else {
            if (!b.isMinus) {
                return -(b + (-a));
            } else {
                return -((-a) + b);
            }
        }
    }

    big_int operator*(const big_int &ob) const {
        auto a = this->clone();
        auto b = ob.clone();
        auto c = big_int(0);
        auto minus = a.isMinus != b.isMinus;
        b.isMinus = false;
        auto bs = b.to_string();
        for (int i = 0; i < bs.length(); ++i) {
            auto currA = a.head->prev;
            for (int j = 0; currA != a.head; ++j) {
                auto s = std::to_string((int) currA->value * (bs[bs.length() - i - 1] - '0'));
                for (int k = 0; k < i + 4 * j; ++k) {
                    s += "0";
                }
                auto d = big_int(s);
                c += d;
                currA = currA->prev;
            }
        }
        c.isMinus = minus;
        return c;
    }

    big_int operator/(const big_int &ob) const {
        if (this->isMinus)
            return -((-*this) / ob);
        if (ob.isMinus)
            return -(*this / (-ob));
        auto d = this->compare_to(ob);
        if (d < 0)
            return 0;
        if (d == 0)
            return 1;
        auto a = this->clone();
        auto b = ob.clone();
        std::string s = "";
        auto a0 = big_int(a.to_string().append(b.get_number_length(), '0'));
        for (int i = a.get_number_length(); i >= 0; --i) {
            auto b0 = big_int(b.to_string().append(i, '0'));
            for (int j = 0;; ++j) {
                if (a0 - b0 < 0) {
                    s += std::to_string(j);
                    break;
                }
//                std::cout << "a0: " << a0 << std::endl << "b0: " << b0 << std::endl << a0.compare_to(b0) << std::endl;
                a0 -= b0;
            }
        }
        s = s.substr(0, s.length() - b.get_number_length());
        return big_int(s);
    }

private:
    bool isMinus = false;
};


#endif //INTEGER_CALCULATOR_BIG_INT_H
