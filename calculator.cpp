//
// Created by hechu on 23-11-20.
//

#include "calculator.h"
#include "iostream"
#include "big_int.h"

int main() {
    calculator::hello("Big Int");
    while (true) {
        try
        {
            std::string exp;
            std::cout << "Please enter an expression: (contains only numbers, arithmetic operators, commas, and parentheses)" << std::endl;
            std::getline(std::cin, exp);
            if (exp.empty())
                throw "Invalid expression";
            auto ans = calculator::solve(exp);
            std::cout << "The result is:" << std::endl;
            std::cout << ans.to_string(true) << std::endl;
        }
        catch (const char* msg)
        {
	        std::cerr << msg << std::endl;
        }
        std::cout << std::endl;
    }
}
