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

void Span::addNumber(int number) {
    checkCapacity();
    _numbers.push_back(number);
}

int Span::shortestSpan() {
    checkEmpty();
    if (_numbers.size() < 2) {
        throw std::runtime_error("MIN 2 numbers");
    }
    std::vector<int> tmp(_numbers.begin(), _numbers.end());
    std::sort(tmp.begin(), tmp.end());
    int minSpan = tmp[1] - tmp[0];
    for (unsigned int i = 1; i < tmp.size(); ++i) {
        int span = tmp[i] - tmp[i - 1];
        if (span < minSpan) {
            minSpan = span;
        }
    }
    return minSpan;
}

int Span::longestSpan() {
    checkEmpty();
    std::vector<int> tmp(_numbers.begin(), _numbers.end());
    std::sort(tmp.begin(), tmp.end());

    if (tmp.size() < 2) {
        throw std::runtime_error("MIN 2 numbers");
    }
    return *(tmp.rbegin()) - *(tmp.begin());
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

void Span::addRange(std::vector<int>::iterator start, std::vector<int>::iterator end) {
   unsigned int rangeSize = std::distance(start, end);
   if (rangeSize + _numbers.size() > _n) {
       throw std::runtime_error("Adding this range would exceed capacity");
   }
    _numbers.insert(_numbers.end(), start, end);
}