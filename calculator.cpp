//
// Created by hechu on 23-11-20.
//

#include "calculator.h"
#include "iostream"
#include "big_int.h"
#include "expression.h"

int main() {
    calculator::Hello("Big Int");
    while (true) {
        expression exp;
        std::cout << "请输入表达式：（仅包含0-9与四则运算符号）" << std::endl;
        std::cin >> exp;
        std::cout << "结果为：" << std::endl;
        std::cout << exp.get_value() << std::endl;
    }
}