//
// Created by hechu on 23-11-20.
//

#ifndef INTEGER_CALCULATOR_CALCULATOR_H
#define INTEGER_CALCULATOR_CALCULATOR_H

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "big_int.h"

const static std::unordered_map<char, int> char_map = {
        {'+', 0},
        {'-', 0},
        {'*', 1},
        {'/', 1},
        {'^', 2},
};

class calculator {
public:
    static void hello(std::string name) {
        std::cout << "Hello, " << name << "!" << std::endl;
    }

    /**
     * 将输入的中缀表达式转化为后缀表达式
     * @param nifix_str 中缀表达式
     * @return 字符串数组，每一个字符串代表一个数字或者运算符
     */
    static std::vector<std::string> nifix_to_postfix(std::string &nifix_str) {
        std::stack<char> operator_sc;
        std::vector<std::string> ans;
        int temp = 0;
        for (int i = 0; i < nifix_str.size(); ++i) {
            if (auto a = nifix_str[i]; char_map.contains(a)) {
                while (!operator_sc.empty()) {
                    char peek = operator_sc.top();
                    if (is_higher(peek, a) < 0 || peek == '(') break;
                    operator_sc.pop();
                    ans.push_back(std::string(1, peek));
                }
                operator_sc.push(a);
            } else if (a == '(' || a == ')') {
                if (a == ')') {
                    while (!operator_sc.empty()) {
                        char peek = operator_sc.top();
                        operator_sc.pop();
                        if (peek == '(') break;
                        ans.push_back(std::string(1, peek));
                    }
                    continue;
                }
                operator_sc.push(a);
            } else if (a >= '0' && a <= '9') {
                int cur = i;
                std::string curStr = "";
                for (; cur < nifix_str.size(); ++cur) {
                    char b = nifix_str[cur];
                    if (b >= '0' && b <= '9')
                        curStr += b;
                    else if (b != ',')
                        break;
                }
                i = cur - 1;
                ans.push_back(std::move(curStr));
            } else if (a == ' ' || a == '\t' || a == ',') {
                continue;
            } else {
                throw "Invalid expression";
            }
        }

        while (!operator_sc.empty()) {
            char peek = operator_sc.top();
            if (peek == '(') throw "Invalid expression";
            operator_sc.pop();
            ans.push_back(std::string(1, peek));
        }
        return ans;
    }

    /**
     * 计算后缀表达式
     */
    static big_int postfix_cal(const std::vector<std::string> &strs) {
        std::stack<big_int> sc;
        for (int i = 0; i < strs.size(); ++i) {
            const std::string &str = strs[i];
            if (str.length() == 1 && char_map.contains(str[0])) {
                if (sc.size() < 2) throw "Invalid expression";
                auto b = sc.top();
                sc.pop();
                auto a = sc.top();
                sc.pop();
                if (str.compare("+") == 0)
                    sc.push(a + b);
                else if (str.compare("-") == 0)
                    sc.push(a - b);
                else if (str.compare("/") == 0)
                    sc.push(a / b);
                else if (str.compare("*") == 0)
                    sc.push(a * b);
                else if (str.compare("^") == 0)
                    sc.push(pow(a, std::stoi(b.to_string())));
            } else {
                auto temp = big_int(str);
                sc.push(temp);
            }
        }

        return sc.top();
    }

    static big_int solve(std::string exp) {
        return postfix_cal(nifix_to_postfix(exp));
    }

private:
    static int is_higher(char c1, char c2) {
        return char_map.at(c1) - char_map.at(c2);
    }
};

int main();

#endif //INTEGER_CALCULATOR_CALCULATOR_H
