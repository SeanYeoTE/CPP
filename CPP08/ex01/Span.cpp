#include "Span.hpp"


Span::Span(unsigned int n) : _n(n) {}


Span::~Span() {}

Span::Span(Span const &other) : _n(other._n), _numbers(other._numbers) {}

Span &Span::operator=(Span const &rhs) {
    if (this != &rhs) {
        _n = rhs._n;
        _numbers = rhs._numbers;
    }
    return *this;
}

void Span::addnumber(int number) {
    checkCapacity();
    _numbers.insert(number);
}

int Span::shortestSpan() {
    checkEmpty();
    if (_numbers.size() < 2) {
        throw std::runtime_error("MIN 2 numbers");
    }
    std::multiset<int>::iterator it = _numbers.begin();
    int minSpan = INT_MAX;
    std::multiset<int>::iterator placeholder = it ++;
    for (std::multiset<int>::iterator nextIt = placeholder; nextIt != _numbers.end(); ++it, ++nextIt) {
        int span = *nextIt - *it;
        std::cout << "Span between " << *it << " and " << *nextIt << " is " << span << std::endl;
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return minSpan;
}

int Span::longestSpan() {
    checkEmpty();
    if (_numbers.size() < 2) {
        throw std::runtime_error("MIN 2 numbers");
    }
    return *(_numbers.rbegin()) - *(_numbers.begin());
}

void Span::checkCapacity() const {
    if (_numbers.size() >= _n) {
        throw std::runtime_error("Max Cap reached");
    }
}

void Span::checkEmpty() const {
    if (_numbers.empty()) {
        throw std::runtime_error("Span is empty, cannot compute spans");
    }
}