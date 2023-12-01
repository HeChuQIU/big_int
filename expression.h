//
// Created by hechu on 23-12-1.
//

#ifndef INTEGER_CALCULATOR_EXPRESSION_H
#define INTEGER_CALCULATOR_EXPRESSION_H


#include <istream>
#include <stack>
#include <map>
#include "big_int.h"

class expression {
public:
    friend std::istream &operator>>(std::istream &in, expression &b);

    expression() = default;

    explicit expression(std::string s) {
        s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }),
                s.end());

        bool getting_num = true;
        size_t pos = 0;
        while (pos < s.length()) {
            if (getting_num) {
                big_int bi;
                pos = big_int::get_big_int_in(s.substr(pos), bi) + pos;
                number_stack.push(bi);
                getting_num = false;
            } else {
                char opt = s[pos];
                pos++;
                if (operator_stack.empty() || opt_order[opt] > opt_order[operator_stack.top()]) {
                    operator_stack.push(opt);
                } else {
                    big_int b = number_stack.top();
                    number_stack.pop();
                    big_int a = number_stack.top();
                    number_stack.pop();
                    big_int c;
                    switch (opt) {
                        case '+':
                            c = a + b;
                            break;
                        case '-':
                            c = a - b;
                            break;
                        case '*':
                            c = a * b;
                            break;
                        case '/':
                            c = a / b;
                            break;
                        default:
                            break;
                    }
                    number_stack.push(c);
                }
                getting_num = true;
            }
        }
    }

    big_int get_value() {
        while (!operator_stack.empty()) {
            char opt = operator_stack.top();
            operator_stack.pop();
            if (opt == '(' || opt == ')')
                continue;
            big_int b = number_stack.top();
            number_stack.pop();
            big_int a = number_stack.top();
            number_stack.pop();
            big_int c;
            switch (opt) {
                case '+':
                    c = a + b;
                    break;
                case '-':
                    c = a - b;
                    break;
                case '*':
                    c = a * b;
                    break;
                case '/':
                    c = a / b;
                    break;
                default:
                    break;
            }
            number_stack.push(c);
        }
        return number_stack.top();
    }

private:
    std::stack<big_int> number_stack;
    std::stack<char> operator_stack;
    std::map<char, int> opt_order = {
            {'+', 0},
            {'-', 0},
            {'*', 1},
            {'/', 1},
            {'(', 2},
            {')', 2}
    };
};


#endif //INTEGER_CALCULATOR_EXPRESSION_H
