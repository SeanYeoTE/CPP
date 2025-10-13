#ifndef SPAN_HPP
#define SPAN_HPP


#include <climits>
#include <vector>
class Span
{
    public:
        Span(unsigned int n);
        ~Span();
        Span(Span const &other);
        Span &operator= (Span const &rhs);
        int operator[](unsigned int index) const;
        void addNumber(int number);
        int shortestSpan();
        int longestSpan();
        void addRange(std::vector<int>::iterator start, std::vector<int>::iterator end);
        int size() const;

    private:
        unsigned int _n;
        std::vector<int> _numbers;

        Span();
        void checkCapacity() const; // Check if we can add more numbers
        void checkEmpty() const; // Check if the set is empty


};

#endif
