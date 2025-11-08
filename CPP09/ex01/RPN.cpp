#include "RPN.hpp"

RPN::RPN(const std::string &expression) : _expression(expression) {}

RPN::RPN(const RPN &other) : _stack(other._stack), _expression(other._expression) {
    // Copy constructor implementation
}

RPN &RPN::operator=(const RPN &other) {
    if (this != &other) {
        _stack = other._stack;
        _expression = other._expression;
    }
    return *this;
}

RPN::~RPN() {
    // Destructor implementation
}


double RPN::Calculate() {
    
    std::istringstream iss(_expression);
    std::string token;
    while (iss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            // If the token is a number
            int num = std::atoi(token.c_str());
            if (num > 9 || num < -9)
                throw std::invalid_argument("Number is not a single digit");
            _stack.push(num);
        } else {
            // If the token is an operator
            if (_stack.size() < 2) {
                throw std::runtime_error("Not enough operands in stack for operation.");
            }
            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            if (token == "+") {
                _stack.push(a + b);
            } else if (token == "-") {
                _stack.push(a - b);
            } else if (token == "*") {
                _stack.push(a * b);
            } else if (token == "/") {
                if (b == 0) {
                    throw std::runtime_error("Division by zero.");
                }
                _stack.push(a / b);
            } else {
                throw std::invalid_argument("Invalid operator: " + token);
            }
        
        }
    }
    if (_stack.size() != 1) {
        throw std::runtime_error("The stack should contain exactly one element after evaluation.");
    }
    return _stack.top();
}
