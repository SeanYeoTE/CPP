#ifndef RPN_HPP
#define RPN_HPP


#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

class RPN
{
    private:
        std::stack<int> _stack;
        std::string _expression;
        
        RPN();
    public:
        double calculate();
        RPN(const std::string &expression);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        
};
#endif